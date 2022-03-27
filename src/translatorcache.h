#ifndef TRANSLATORCACHE_H
#define TRANSLATORCACHE_H

#include "word.h"

class TranslatorCache
{
public:
    TranslatorCache();
    ~TranslatorCache();

    bool get(Word& word) const;
    bool store(const Word& word);
    void clear();

private:
    // TODO: add lazy load/save
    bool save() const;
    bool load();

    // Add mutexes
    QVector<QMap<QString, Word>> m_alphabetFiles;
};

#endif // TRANSLATORCACHE_H
