#include "tst_translator.h"

QList<QString> WordsToTranslate = {
    "cross",
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
    "carefully",
};

const QString ApiKeyFileName = "yandexDictionaryKey.txt";

void TestTranslator::initTestCase()
{
    QVERIFY(translator.initialize(ApiKeyFileName));
}

void TestTranslator::cleanupTestCase() {}

void TestTranslator::testTranslate()
{
    foreach(auto word, WordsToTranslate)
    {
        Word w(word);
        QVERIFY(translator.translate(w));
        continue;
    }
}
