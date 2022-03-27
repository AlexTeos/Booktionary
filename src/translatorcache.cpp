#include "translatorcache.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

TranslatorCache::TranslatorCache()
{
    m_alphabetFiles.resize(26);
    load();
}

TranslatorCache::~TranslatorCache()
{
    save();
}

bool TranslatorCache::get(Word& word) const
{
    char firstLetter = word.word().toLower().toLatin1()[0];
    if (firstLetter < 97 or firstLetter > 122) return false;

    qint8 alhpabetIndex = firstLetter - 97;
    if (!m_alphabetFiles[alhpabetIndex].contains(word.word())) return false;

    word = m_alphabetFiles[alhpabetIndex][word.word()];

    return true;
}

bool TranslatorCache::store(const Word& word)
{
    char firstLetter = word.word().toLower().toLatin1()[0];
    if (firstLetter < 97 or firstLetter > 122) return false;

    qint8 alhpabetIndex = firstLetter - 97;
    if (!m_alphabetFiles[alhpabetIndex].contains(word.word()))
    {
        m_alphabetFiles[alhpabetIndex].insert(word.word(), word);
    }

    return true;
}

void TranslatorCache::clear()
{
    for (auto& wordMap : m_alphabetFiles)
    {
        wordMap.clear();
    }
}

bool TranslatorCache::save() const
{
    QDir().mkpath("translatorCache/");

    char letter = '@';
    for (const auto& wordMap : m_alphabetFiles)
    {
        ++letter;

        QFile saveFile("translatorCache/" + QString(letter) + ".json");

        if (not wordMap.size())
        {
            saveFile.remove();
            continue;
        }

        if (!saveFile.open(QIODevice::WriteOnly)) return false;

        QJsonArray wordsJsonArray;

        for (const auto& word : wordMap)
            wordsJsonArray.append(word.toJson());

        QJsonObject wordsJsonObject;
        wordsJsonObject.insert("words", wordsJsonArray);

        saveFile.write(QJsonDocument(wordsJsonObject).toJson());

        saveFile.close();
    }

    return true;
}

bool TranslatorCache::load()
{
    if (not QDir().exists("translatorCache/")) return false;

    char letter = '@';

    for (auto& wordMap : m_alphabetFiles)
    {
        ++letter;

        QFile loadFile("translatorCache/" + QString(letter) + ".json");

        if (!loadFile.exists() || !loadFile.open(QIODevice::ReadOnly)) continue;

        QJsonDocument jsonDocument(QJsonDocument::fromJson(loadFile.readAll()));
        loadFile.close();
        QJsonObject jsonObject = jsonDocument.object();

        if (!jsonObject.contains("words") || !jsonObject["words"].isArray()) continue;

        QJsonArray wordsJsonArray = jsonObject["words"].toArray();

        for (const auto& wordJson : wordsJsonArray)
        {
            Word word(wordJson.toObject());

            wordMap.insert(word.word(), word);
        }
    }

    return true;
}
