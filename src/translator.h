#ifndef TRANSLATOR_H
#define TRANSLATOR_H

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
    bool         translate(Word& word);
    PartOfSpeach localPOStoWordPOS(const QString localPOS);

private:
    bool parseResultAndFillWord(const QByteArray& reply, Word& word);
    bool getTranslation(QByteArray& reply, const Word& word);
    bool loadKey(const QString& keyFileName, QString Key);

    QString         apiKey;
    TranslatorState state;
};

#endif // TRANSLATOR_H
