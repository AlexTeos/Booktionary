#include "tst_outputgenerator.h"

#include "../src/dictionarymodel.h"

void TestOutputGenerator::initTestCase()
{
    m_outputGenerator.setDictionaryModel(&m_dictionary);
}

void TestOutputGenerator::cleanupTestCase() {}

void TestOutputGenerator::testGenerateOutput()
{
    DictionaryModel dictionary;
    {
        Word word("defeat");
        {
            Definition definition;

            definition.m_meanings.push_back("поражение");

            definition.m_pos = PartOfSpeach::Noun;

            definition.m_examples.push_back(OriginalAndTranslation("military defeat", "военное поражение"));
            definition.m_examples.push_back(OriginalAndTranslation("cause of his defeat", "причина его поражения"));
            definition.m_examples.push_back(OriginalAndTranslation("suffer defeat", "потерпеть поражение"));

            word.addDefinition(definition);
        }
        {
            Definition definition;

            definition.m_pos = PartOfSpeach::Verb;

            definition.m_meanings.push_back("одержать победу");
            definition.m_meanings.push_back("разгромить");
            definition.m_meanings.push_back("нанести поражение");
            definition.m_meanings.push_back("поразить");
            definition.m_meanings.push_back("потерпеть поражение");
            definition.m_meanings.push_back("расстроить");

            definition.m_examples.push_back(OriginalAndTranslation("defeated country", "побежденная страна"));

            word.addDefinition(definition);
        }
        {
            Definition definition;

            definition.m_pos = PartOfSpeach::Adjective;

            definition.m_meanings.push_back("поверженный");

            word.addDefinition(definition);
        }
        dictionary.addWord(word);
    }
    {
        Word word("depressed");
        {
            Definition definition;

            definition.m_pos = PartOfSpeach::Participle;

            definition.m_meanings.push_back("подавленный");
            definition.m_meanings.push_back("сплющенный");
            definition.m_meanings.push_back("отжатый");
            definition.m_meanings.push_back("сниженный");
            definition.m_meanings.push_back("ослабленный");

            definition.m_examples.push_back(OriginalAndTranslation("Such weather depressed me.", ""));

            word.addDefinition(definition);
        }
        {
            Definition definition;

            definition.m_pos = PartOfSpeach::Adjective;

            definition.m_meanings.push_back("унылый");
            definition.m_meanings.push_back("депрессивный");
            definition.m_meanings.push_back("понурый");

            definition.m_examples.push_back(
                OriginalAndTranslation("He seemed a bit depressed about his work situation.", ""));
            definition.m_examples.push_back(
                OriginalAndTranslation("She became deeply depressed when her husband died.", ""));

            word.addDefinition(definition);
        }
        dictionary.addWord(word);
    }
    {
        Word word("catch up");
        {
            Definition definition;

            definition.m_pos = PartOfSpeach::Verb;

            definition.m_meanings.push_back("догнать");
            definition.m_meanings.push_back("наверстать упущенное");
            definition.m_meanings.push_back("поспевать");
            definition.m_meanings.push_back("подтянуться");

            word.addDefinition(definition);
        }
        dictionary.addWord(word);
    }

    QVERIFY(m_outputGenerator.generateOutput("testDictionary.dict"));

    QFile::remove("testDictionary.dict");
}
