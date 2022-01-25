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

            definition.meaning.push_back("поражение");

            definition.examples.push_back(OriginalAndTranslation("military defeat", "военное поражение"));
            definition.examples.push_back(OriginalAndTranslation("cause of his defeat", "причина его поражения"));
            definition.examples.push_back(OriginalAndTranslation("suffer defeat", "потерпеть поражение"));

            word.addDefinition(PartOfSpeach::Noun, definition);
        }
        {
            Definition definition;

            definition.meaning.push_back("одержать победу");
            definition.meaning.push_back("разгромить");
            definition.meaning.push_back("нанести поражение");
            definition.meaning.push_back("поразить");
            definition.meaning.push_back("потерпеть поражение");
            definition.meaning.push_back("расстроить");

            definition.examples.push_back(OriginalAndTranslation("defeated country", "побежденная страна"));

            word.addDefinition(PartOfSpeach::Verb, definition);
        }
        {
            Definition definition;

            definition.meaning.push_back("поверженный");

            word.addDefinition(PartOfSpeach::Adjective, definition);
        }
        dictionary.addWord(word);
    }
    {
        Word word("depressed");
        {
            Definition definition;

            definition.meaning.push_back("подавленный");
            definition.meaning.push_back("сплющенный");
            definition.meaning.push_back("отжатый");
            definition.meaning.push_back("сниженный");
            definition.meaning.push_back("ослабленный");

            definition.examples.push_back(OriginalAndTranslation("Such weather depressed me.", ""));

            word.addDefinition(PartOfSpeach::Participle, definition);
        }
        {
            Definition definition;

            definition.meaning.push_back("унылый");
            definition.meaning.push_back("депрессивный");
            definition.meaning.push_back("понурый");

            definition.examples.push_back(
                OriginalAndTranslation("He seemed a bit depressed about his work situation.", ""));
            definition.examples.push_back(
                OriginalAndTranslation("She became deeply depressed when her husband died.", ""));

            word.addDefinition(PartOfSpeach::Adjective, definition);
        }
        dictionary.addWord(word);
    }
    {
        Word word("catch up");
        {
            Definition definition;

            definition.meaning.push_back("догнать");
            definition.meaning.push_back("наверстать упущенное");
            definition.meaning.push_back("поспевать");
            definition.meaning.push_back("подтянуться");

            word.addDefinition(PartOfSpeach::Verb, definition);
        }
        dictionary.addWord(word);
    }

    QVERIFY(m_outputGenerator.generateOutput("testDictionary.dict"));

    QFile::remove("testDictionary.dict");
}
