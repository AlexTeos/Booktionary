#ifndef WORD_H
#define WORD_H

#include <QJsonValue>
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

inline PartOfSpeach StringPosToEnumPos(const QString& pos)
{
    QString posLower = pos.toLower();
    if (posLower == "verb")
        return PartOfSpeach::Verb;
    else if (posLower == "noun")
        return PartOfSpeach::Noun;
    else if (posLower == "adjective")
        return PartOfSpeach::Adjective;
    else if (posLower == "determiner")
        return PartOfSpeach::Determiner;
    else if (posLower == "adverb")
        return PartOfSpeach::Adverb;
    else if (posLower == "pronoun")
        return PartOfSpeach::Pronoun;
    else if (posLower == "preposition")
        return PartOfSpeach::Preposition;
    else if (posLower == "conjunction")
        return PartOfSpeach::Conjunction;
    else if (posLower == "interjection")
        return PartOfSpeach::Interjection;
    else if (posLower == "participle")
        return PartOfSpeach::Participle;
    else
        return PartOfSpeach::Unknown;
}

typedef QPair<QString, QString>         OriginalAndTranslation;
typedef QVector<OriginalAndTranslation> OriginalAndTranslationList;

struct Definition
{
    Definition(){};
    explicit Definition(const QJsonObject& definitionJson);

    using const_iterator = OriginalAndTranslationList::const_iterator;
    const_iterator begin() const { return m_examples.cbegin(); }
    const_iterator end() const { return m_examples.cend(); }

    OriginalAndTranslationList m_examples;
    QStringList                m_meanings;
    PartOfSpeach               m_pos = PartOfSpeach::Unknown;

    QJsonValue toJson() const;
};

class Word
{
public:
    Word() {}
    Word(const QString& word) : m_word(word), m_state(WordState::Untranslated) {}
    explicit Word(const QJsonObject& jsonWord);

    typedef QMultiMap<PartOfSpeach, Definition> Definitions;
    void                                        addDefinition(const Definition& definition);

    using const_iterator = Definitions::const_iterator;
    const_iterator begin() const { return m_definitions.cbegin(); }
    const_iterator end() const { return m_definitions.cend(); }

    WordState::WordState state() const;
    QString              word() const;
    QStringList          meanings() const;

    QJsonValue toJson() const;

    void setState(WordState::WordState newState);

private:
    Definitions          m_definitions;
    QString              m_word;
    WordState::WordState m_state;
};

#endif // WORD_H
