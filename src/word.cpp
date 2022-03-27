#include "word.h"

#include <QJsonArray>
#include <QJsonObject>

Word::Word(const QJsonObject& jsonWord)
{
    if (jsonWord.contains("word") && jsonWord["word"].isString())
        m_word = jsonWord["word"].toString();
    else
        return;

    m_state = WordState::TranslationNotFound;

    if (jsonWord.contains("definitions") && jsonWord["definitions"].isArray())
    {
        QJsonArray definitionJsonArray = jsonWord["definitions"].toArray();

        for (const auto& definitionJson : definitionJsonArray)
        {
            Definition definition(definitionJson.toObject());

            m_definitions.insert(definition.m_pos, definition);
        }

        m_state = WordState::Translated;
    }
}

void Word::addDefinition(const Definition& definition)
{
    if (not m_definitions.contains(definition.m_pos)) m_definitions.insert(definition.m_pos, definition);
}

QString Word::word() const
{
    return m_word;
}

QStringList Word::meanings() const
{
    QStringList out;
    out.reserve(m_definitions.size());
    QMultiMapIterator<PartOfSpeech, Definition> i(m_definitions);
    while (i.hasNext())
    {
        i.next();
        out.push_back(PartOfSpeechumToQString[i.key()] + ": " + i.value().m_meanings.join(", "));
    }
    return out;
}

QJsonValue Word::toJson() const
{
    QJsonObject wordJsonObject;
    wordJsonObject.insert("word", m_word);

    QJsonArray definitionsJsonArray;
    for (const auto& definition : m_definitions)
    {
        definitionsJsonArray.append(definition.toJson());
    }

    if (definitionsJsonArray.size()) wordJsonObject.insert("definitions", definitionsJsonArray);

    return wordJsonObject;
}

void Word::setState(WordState::WordState newState)
{
    m_state = newState;
}

WordState::WordState Word::state() const
{
    return m_state;
}

Definition::Definition(const QJsonObject& definitionJson)
{
    if (definitionJson.contains("meanings") && definitionJson["meanings"].isArray())
    {
        QJsonArray meaningsJsonArray = definitionJson["meanings"].toArray();

        for (const auto& meaningJson : meaningsJsonArray)
        {
            if (meaningJson.isString()) m_meanings.append(meaningJson.toString());
        }
    }

    if (definitionJson.contains("part_of_speech") && definitionJson["part_of_speech"].isString())
    {
        m_pos = StringPosToEnumPos(definitionJson["part_of_speech"].toString());
    }

    if (definitionJson.contains("examples") && definitionJson["examples"].isArray())
    {
        QJsonArray examplesJsonArray = definitionJson["examples"].toArray();

        for (const auto& exampleJson : examplesJsonArray)
        {
            if (exampleJson.isObject())
            {
                QJsonObject exampleJsonObject = exampleJson.toObject();
                if (exampleJsonObject.keys().size() > 0)
                {
                    QString example = exampleJsonObject.keys()[0];
                    QString translation;
                    if (exampleJsonObject.value(example).isString())
                    {
                        translation = exampleJsonObject.value(example).toString();
                    }
                    m_examples.append(OriginalAndTranslation(example, translation));
                }
            }
        }
    }
}

QJsonValue Definition::toJson() const
{
    QJsonObject jsonObject;

    QJsonArray meaningsArray;

    for (const auto& meaning : m_meanings)
        meaningsArray.append(meaning);

    QJsonArray examplessArray;

    for (const auto& example : m_examples)
    {
        QJsonObject exampleJsonObject;
        exampleJsonObject.insert(example.first, example.second);
        examplessArray.append(exampleJsonObject);
    }

    jsonObject.insert("meanings", meaningsArray);
    jsonObject.insert("examples", examplessArray);
    jsonObject.insert("part_of_speech", PartOfSpeechumToQString[m_pos]);

    return jsonObject;
}
