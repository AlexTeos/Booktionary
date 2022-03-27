#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QNetworkAccessManager>

#include "translatorcache.h"

enum TranslatorState
{
    Uninitialized = 0,
    InitializationError,
    Initialized
};

class Translator
{
public:
    Translator();
    Translator(const QString& keyFileName);
    bool initialize(const QString& keyFileName);
    bool translate(Word& word, QNetworkAccessManager* networkManager = nullptr);
    bool translateN(QList<Word>::iterator iter, qsizetype n);
    bool translateNMT(QList<Word>::iterator iter, qsizetype n);
    void clearCache();

private:
    bool parseResultAndFillWord(const QByteArray& reply, Word& word);
    bool getTranslation(QByteArray& reply, const Word& word, QNetworkAccessManager* networkManager);
    bool loadKey(const QString& keyFileName, QString Key);

    QString         m_apiKey;
    TranslatorState m_state;
    TranslatorCache m_cache;
};

#endif // TRANSLATOR_H
