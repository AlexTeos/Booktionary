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
    Interjection,
    Participle
};

typedef QPair<QString, QString>         OriginalAndTranslation;
typedef QVector<OriginalAndTranslation> OriginalAndTranslationList;

struct Definition
{
    using const_iterator = OriginalAndTranslationList::const_iterator;
    const_iterator begin() const { return examples.cbegin(); }
    const_iterator end() const { return examples.cend(); }

    OriginalAndTranslationList examples;
    QStringList                meaning;
};

class Word
{
public:
    Word(const QString& _word) : word(_word) {}

    typedef QMultiMap<PartOfSpeach, Definition> Definitions;
    void    addDefinition(const PartOfSpeach& PartOfSpeach, const Definition& definition);
    QString getWord() const;

    using const_iterator = Definitions::const_iterator;
    const_iterator begin() const { return definitions.cbegin(); }
    const_iterator end() const { return definitions.cend(); }

private:
    Definitions definitions;
    QString     word;
};

#endif // WORD_H
