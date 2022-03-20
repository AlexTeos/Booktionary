#include "translator.h"

#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <future>
#include <thread>

Translator::Translator() {}

Translator::Translator(const QString& keyFileName) : state(TranslatorState::Uninitialized)
{
    initialize(keyFileName);
}

bool Translator::initialize(const QString& keyFileName)
{
    if (loadKey(keyFileName, apiKey))
    {
        QScopedPointer<QNetworkAccessManager> threadNetworkManager(new QNetworkAccessManager());
        QByteArray                            tmp;
        if (getTranslation(tmp, Word("the"), threadNetworkManager.get()))
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

bool Translator::getTranslation(QByteArray& reply, const Word& word, QNetworkAccessManager* networkManager)
{
    if (state != TranslatorState::Initialized) return false;

    QNetworkRequest request;
    QNetworkReply*  _reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setUrl(QUrl("https://dictionary.yandex.net/api/v1/dicservice.json/"
                        "lookup?key=" +
                        apiKey + "&lang=en-ru&text=" + word.word()));
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");

    QEventLoop loop;
    _reply = networkManager->get(request);
    QObject::connect(_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    reply = _reply->readAll();

    _reply->deleteLater();

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

bool Translator::translate(Word& word, QNetworkAccessManager* networkManager)
{
    QByteArray translation;
    if (networkManager == nullptr)
    {
        QScopedPointer<QNetworkAccessManager> localNetworkManager(new QNetworkAccessManager());
        if (not getTranslation(translation, word, localNetworkManager.get())) return false;
    }
    else
    {
        if (not getTranslation(translation, word, networkManager)) return false;
    }

    if (not parseResultAndFillWord(translation, word)) return false;
    return true;
}

bool Translator::translateN(QList<Word>::iterator iter, qsizetype n)
{
    bool res = true;

    QScopedPointer<QNetworkAccessManager> threadNetworkManager(new QNetworkAccessManager());
    for (qsizetype i = 0; i < n; ++i, ++iter)
    {
        res &= translate(*iter, threadNetworkManager.get());
    }

    return res;
}

bool Translator::translateNMT(QList<Word>::iterator iter, qsizetype n)
{
    // TODO: use QFuture
    qint16    threadCount    = std::thread::hardware_concurrency() * 4;
    qsizetype wordsPerThread = n >= threadCount ? n / threadCount : n;

    std::vector<std::future<bool>> results;
    for (qsizetype i = 0; i < n; iter += wordsPerThread, i += wordsPerThread)
    {
        wordsPerThread = qMin(n - i, wordsPerThread);

        results.push_back(std::async(&Translator::translateN, this, iter, wordsPerThread));
    }

    bool res = true;
    for (auto& result : results)
    {
        res &= result.get();
    }

    return res;
}
