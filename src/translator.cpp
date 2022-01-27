#include "translator.h"

#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

Translator::Translator() {}

Translator::Translator(const QString& keyFileName) : state(TranslatorState::Uninitialized)
{
    initialize(keyFileName);
}

bool Translator::initialize(const QString& keyFileName)
{
    if (loadKey(keyFileName, apiKey))
    {
        QByteArray tmp;
        if (getTranslation(tmp, Word("the")))
        {
            state = TranslatorState::Initialized;
            return true;
        }
    }

    state = TranslatorState::InitializationError;
    return false;
}

PartOfSpeach Translator::localPOStoWordPOS(const QString localPOS)
{
    if (localPOS == "verb")
        return PartOfSpeach::Verb;
    else if (localPOS == "noun")
        return PartOfSpeach::Noun;
    else if (localPOS == "adjective")
        return PartOfSpeach::Adjective;
    else if (localPOS == "determiner")
        return PartOfSpeach::Determiner;
    else if (localPOS == "adverb")
        return PartOfSpeach::Adverb;
    else if (localPOS == "pronoun")
        return PartOfSpeach::Pronoun;
    else if (localPOS == "preposition")
        return PartOfSpeach::Preposition;
    else if (localPOS == "conjunction")
        return PartOfSpeach::Conjunction;
    else if (localPOS == "interjection")
        return PartOfSpeach::Interjection;
    else if (localPOS == "participle")
        return PartOfSpeach::Participle;
    else
        return PartOfSpeach::Unknown;
}

bool Translator::parseResultAndFillWord(const QByteArray& reply, Word& word)
{
    QJsonDocument jsonDocument(QJsonDocument::fromJson(reply));
    QJsonObject   jsonObject     = jsonDocument.object();
    QJsonValue    jsonObjectDef  = jsonObject.take("def");
    QJsonArray    partOfSpeaches = jsonObjectDef.toArray();

    foreach(QJsonValueRef partOfSpeach, partOfSpeaches)
    {
        QString    partofspch   = partOfSpeach.toObject().take("pos").toString();
        QJsonArray translations = partOfSpeach.toObject().take("tr").toArray();
        Definition definition;
        foreach(QJsonValueRef translation, translations)
        {
            definition.meaning.push_back(translation.toObject().take("text").toString());

            QJsonArray examples = translation.toObject().take("ex").toArray();

            foreach(QJsonValueRef example, examples)
            {
                QString exampleText = example.toObject().take("text").toString();

                QJsonArray exampleTranslationArray = example.toObject().take("tr").toArray();
                QString    exampleTranslationText;
                foreach(QJsonValueRef exampleTranslation, exampleTranslationArray)
                {
                    exampleTranslationText += exampleTranslation.toObject().take("text").toString();
                    definition.examples.push_back(OriginalAndTranslation(exampleText, exampleTranslationText));
                }
            }
        }
        word.addDefinition(localPOStoWordPOS(partofspch), definition);
    }

    word.setState(partOfSpeaches.size() ? WordState::Translated : WordState::TranslationNotFound);

    return true;
}

bool Translator::getTranslation(QByteArray& reply, const Word& word)
{
    if (state != TranslatorState::Initialized) return false;

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest        request;
    QNetworkReply*         _reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setUrl(QUrl("https://dictionary.yandex.net/api/v1/dicservice.json/"
                        "lookup?key=" +
                        apiKey + "&lang=en-ru&text=" + word.word()));
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");

    QEventLoop loop;
    _reply = manager->get(request);
    QObject::connect(_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    reply = _reply->readAll();
    delete manager;

    return true;
}

bool Translator::loadKey(const QString& keyFileName, QString Key)
{
    QFile keyFile(keyFileName);
    if (keyFile.exists())
    {
        keyFile.open(QIODevice::ReadOnly);
        apiKey = keyFile.readAll();
        state  = TranslatorState::Initialized;
        return true;
    }

    state = TranslatorState::InitializationError;

    return false;
}

bool Translator::translate(Word& word)
{
    QByteArray translation;
    if (not getTranslation(translation, word)) return false;
    if (not parseResultAndFillWord(translation, word)) return false;
    return true;
}
