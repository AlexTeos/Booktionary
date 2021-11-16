#ifndef WORD_H
#define WORD_H

#include <QList>
#include <QMultiMap>
#include <QPair>
#include <QVector>

enum PartOfSpeach
{
    Unknown = 0,
    Verb,
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

    OriginalAndTranslation examples;
    QStringList            meaning;
    QStringList            syn;
};

class Word
{
public:
    Word(const QString& _word) : word(_word) {}

    void    addDefinition(const PartOfSpeach& PartOfSpeach, const Definiton& definiton);
    QString getWord() const;

private:
    typedef QMultiMap<PartOfSpeach, Definiton> Definitons;
    Definitons                                 definitions;
    QString                                    word;
};

#endif // WORD_H
