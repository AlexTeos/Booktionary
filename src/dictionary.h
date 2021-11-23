#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "word.h"

enum DictionaryState
{
    Untranslated = 0,
    Translating,
    Translated
};

class Dictionary
{
public:
    explicit Dictionary(const QList<QString>& wordList);

private:
    QVector<Word>   dictionary;
    DictionaryState state;
};

#endif // DICTIONARY_H
