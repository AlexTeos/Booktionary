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

enum PartOfSpeech
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

const QString PartOfSpeechumToQString[11] = {"Unknown",
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

inline PartOfSpeech StringPosToEnumPos(const QString& pos)
{
    QString posLower = pos.toLower();
    if (posLower == "verb")
        return PartOfSpeech::Verb;
    else if (posLower == "noun")
        return PartOfSpeech::Noun;
    else if (posLower == "adjective")
        return PartOfSpeech::Adjective;
    else if (posLower == "determiner")
        return PartOfSpeech::Determiner;
    else if (posLower == "adverb")
        return PartOfSpeech::Adverb;
    else if (posLower == "pronoun")
        return PartOfSpeech::Pronoun;
    else if (posLower == "preposition")
        return PartOfSpeech::Preposition;
    else if (posLower == "conjunction")
        return PartOfSpeech::Conjunction;
    else if (posLower == "interjection")
        return PartOfSpeech::Interjection;
    else if (posLower == "participle")
        return PartOfSpeech::Participle;
    else
        return PartOfSpeech::Unknown;
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
    PartOfSpeech               m_pos = PartOfSpeech::Unknown;

    QJsonValue toJson() const;
};

class Word
{
public:
    Word() {}
    Word(const QString& word) : m_word(word), m_state(WordState::Untranslated) {}
    explicit Word(const QJsonObject& jsonWord);

    typedef QMultiMap<PartOfSpeech, Definition> Definitions;
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
