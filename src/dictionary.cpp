#include "dictionary.h"

Dictionary::Dictionary(const QList<QString>& wordList) : state(DictionaryState::Untranslated)
{
    dictionary.reserve(wordList.size());
    foreach(auto word, wordList) { dictionary.push_back(word); }
}
