#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>
#include <QMultiMap>
#include <QPair>
#include <QVector>

enum State
{
    Untranslated = 0,
    Processed,
    Translated
};
typedef State DictionaryState;
typedef State WordState;

enum PartOfSpeach
{
    Verb = 0,
    Noun,
    Adjective,
    Determiner,
    Adverb,
    Pronoun,
    Preposition,
    Conjunction,
    Interjection
};

struct Definiton
{
    typedef QVector<QPair<QString, QString>> OriginalAndTranslation;
    OriginalAndTranslation                   meaning;
    OriginalAndTranslation                   example;
};

class Word
{
public:
    Word(const QString& _word) : word(_word), state(WordState::Untranslated) {}

private:
    typedef QMultiMap<PartOfSpeach, Definiton> Definitons;
    Definitons                                 definitions;
    QString                                    word;
    WordState                                  state;
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
