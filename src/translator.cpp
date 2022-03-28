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

Translator::Translator(const QString& keyFileName) : m_state(TranslatorState::Uninitialized)
{
    initialize(keyFileName);
}

bool Translator::initialize(const QString& keyFileName)
{
    if (loadKey(keyFileName, m_apiKey))
    {
        QScopedPointer<QNetworkAccessManager> threadNetworkManager(new QNetworkAccessManager());
        QByteArray                            tmp;
        if (getTranslation(tmp, Word("the"), threadNetworkManager.get()))
        {
            m_state = TranslatorState::Initialized;
            return true;
        }
    }

    m_state = TranslatorState::InitializationError;
    return false;
}

void Translator::clearCache()
{
    m_cache.clear();
}

bool Translator::parseResultAndFillWord(const QByteArray& reply, Word& word)
{
    QJsonDocument jsonDocument(QJsonDocument::fromJson(reply));
    if (not jsonDocument.isObject()) return false;
    QJsonObject jsonObject = jsonDocument.object();
    if (not jsonObject.contains("def") or not jsonObject["def"].isArray()) return false;

    QJsonArray definitionJsonArray = jsonObject["def"].toArray();
    for (const auto& definitionJson : definitionJsonArray)
    {
        if (not definitionJson.isObject()) continue;

        Definition definition;

        QJsonObject definitionObject = definitionJson.toObject();
        if (definitionObject.contains("pos") and definitionObject["pos"].isString())
            definition.m_pos = StringPosToEnumPos(definitionObject["pos"].toString());

        if (definitionObject.contains("tr") and definitionObject["tr"].isArray())
        {
            QJsonArray translationsJsonArray = definitionObject["tr"].toArray();
            for (const auto& translationJson : translationsJsonArray)
            {
                if (not translationJson.isObject()) continue;

                QJsonObject translation = translationJson.toObject();
                if (translation.contains("text") and translation["text"].isString())
                    definition.m_meanings.append(translation["text"].toString());

                if (translation.contains("ex") and translation["ex"].isArray())
                {
                    QJsonArray examplesJsonArray = translation["ex"].toArray();
                    for (const auto& exampleJson : examplesJsonArray)
                    {
                        if (not exampleJson.isObject()) continue;

                        QJsonObject exampleObject = exampleJson.toObject();

                        QString example;
                        if (exampleObject.contains("text") and exampleObject["text"].isString())
                            example = exampleObject["text"].toString();

                        if (exampleObject.contains("tr") and exampleObject["tr"].isArray())
                        {
                            QJsonArray exampleTranslationArray = exampleObject["tr"].toArray();
                            QString    exampleTranslationText;
                            for (const auto& exampleTranslationJson : exampleTranslationArray)
                            {
                                if (not exampleTranslationJson.isObject()) continue;

                                QJsonObject exampleTranslationObject = exampleTranslationJson.toObject();

                                if (exampleTranslationObject.contains("text") and
                                    exampleTranslationObject["text"].isString())
                                    exampleTranslationText = exampleTranslationObject["text"].toString();
                            }

                            definition.m_examples.push_back(OriginalAndTranslation(example, exampleTranslationText));
                        }
                    }
                }
            }
        }
        word.addDefinition(definition);
    }

    word.setState(definitionJsonArray.size() ? WordState::Translated : WordState::TranslationNotFound);

    return true;
}

bool Translator::getTranslation(QByteArray& reply, const Word& word, QNetworkAccessManager* networkManager)
{
    if (m_state != TranslatorState::Initialized) return false;

    QNetworkRequest request;
    QNetworkReply*  _reply = NULL;

    // TODO: try to use flags
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setUrl(QUrl("https://dictionary.yandex.net/api/v1/dicservice.json/"
                        "lookup?key=" +
                        m_apiKey + "&lang=en-ru&text=" + word.word()));
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
        m_apiKey = keyFile.readAll();
        m_state  = TranslatorState::Initialized;
        return true;
    }

    m_state = TranslatorState::InitializationError;

    return false;
}

bool Translator::translate(Word& word, QNetworkAccessManager* networkManager)
{
    bool isWordCached = m_cache.get(word);

    // TODO: change to if (word.m_state != WordState::Translated)
    if (!isWordCached)
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

        // TODO: Handle network errors
        if (not parseResultAndFillWord(translation, word)) return false;

        m_cache.store(word);
    }

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
