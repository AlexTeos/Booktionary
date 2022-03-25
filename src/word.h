#ifndef WORD_H
#define WORD_H

#include <QList>
#include <QMultiMap>
#include <QPair>
#include <QVector>

namespace WordState
{
enum WordState
{
    Untranslated = 0,
    Translated,
    TranslationNotFound
};
}

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

const QString PartOfSpeachumToQString[11] = {"Unknown",
                                             "Verb",
                                             "Noun",
                                             "Adjective",
                                             "Determiner",
                                             "Adverb",
                                             "Pronoun",
                                             "Preposition",
                                             "Conjunction",
                                             "Interjection",
                                             "Participle"};

typedef QPair<QString, QString>         OriginalAndTranslation;
typedef QVector<OriginalAndTranslation> OriginalAndTranslationList;

struct Definition
{
    using const_iterator = OriginalAndTranslationList::const_iterator;
    const_iterator begin() const { return m_examples.cbegin(); }
    const_iterator end() const { return m_examples.cend(); }

    OriginalAndTranslationList m_examples;
    QStringList                m_meanings;
};

class Word
{
public:
    Word(const QString& word) : m_word(word), m_state(WordState::Untranslated) {}

    typedef QMultiMap<PartOfSpeach, Definition> Definitions;
    void addDefinition(const PartOfSpeach& PartOfSpeach, const Definition& definition);

    using const_iterator = Definitions::const_iterator;
    const_iterator begin() const { return m_definitions.cbegin(); }
    const_iterator end() const { return m_definitions.cend(); }

    WordState::WordState state() const;
    QString              word() const;
    QStringList          meanings() const;

    void setState(WordState::WordState newState);

private:
    Definitions          m_definitions;
    QString              m_word;
    WordState::WordState m_state;
};

#endif // WORD_H
