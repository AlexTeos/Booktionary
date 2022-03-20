#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QNetworkAccessManager>

#include "word.h"

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
    bool         initialize(const QString& keyFileName);
    bool         translate(Word& word, QNetworkAccessManager* networkManager = nullptr);
    bool         translateN(QList<Word>::iterator iter, qsizetype n);
    bool         translateNMT(QList<Word>::iterator iter, qsizetype n);
    PartOfSpeach localPOStoWordPOS(const QString localPOS);

private:
    bool parseResultAndFillWord(const QByteArray& reply, Word& word);
    bool getTranslation(QByteArray& reply, const Word& word, QNetworkAccessManager* networkManager);
    bool loadKey(const QString& keyFileName, QString Key);

    QString         apiKey;
    TranslatorState state;
};

#endif // TRANSLATOR_H
