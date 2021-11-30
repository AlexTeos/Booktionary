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
    explicit Dictionary(const QList<Word>& _dictionary, const DictionaryState& _state);

    using const_iterator = QVector<Word>::const_iterator;
    const_iterator begin() const { return dictionary.cbegin(); }
    const_iterator end() const { return dictionary.cend(); }

private:
    QList<Word>     dictionary;
    DictionaryState state;
};

#endif // DICTIONARY_H
