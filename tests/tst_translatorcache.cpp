#include "tst_translatorcache.h"

QList<QString> WordsToStore = {"cross",
                               "cow",
                               "cow-cow",
                               "a",
                               "across",
                               "crowded",
                               "crossing",
                               "the",
                               "if",
                               "you",
                               "must",
                               "course",
                               "coarse",
                               "carefully"};

void TestTranslatorCache::initTestCase() {}

void TestTranslatorCache::cleanupTestCase() {}

void TestTranslatorCache::testAll()
{
    {
        TranslatorCache cache;

        cache.clear();

        foreach(auto word, WordsToStore)
        {
            Word w(word);
            w.setState(WordState::Translated);

            Definition definition;
            definition.m_pos = PartOfSpeach::Noun;
            definition.m_meanings.push_back("значение");
            definition.m_examples.push_back(OriginalAndTranslation("example1", "пример1"));
            definition.m_examples.push_back(OriginalAndTranslation("example2", "пример2"));

            w.addDefinition(definition);

            QVERIFY(cache.store(w));
        }
    }

    TranslatorCache cache;

    foreach(auto word, WordsToStore)
    {
        Word w(word);
        QVERIFY(cache.get(w));

        QVERIFY(w.state() == WordState::Translated);
        foreach(const Definition& definition, w)
        {
            QVERIFY(definition.m_meanings.size() == 1);
            QVERIFY(definition.m_meanings[0] == "значение");
            QVERIFY(definition.m_pos == PartOfSpeach::Noun);

            int i = 1;
            foreach(const OriginalAndTranslation& example, definition)
            {
                QVERIFY(example.first == "example" + QString::number(i));
                QVERIFY(example.second == "пример" + QString::number(i++));
            }
        }
    }
}
