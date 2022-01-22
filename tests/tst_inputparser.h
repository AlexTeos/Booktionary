#include <QtAlgorithms>
#include <QtTest>

#include "../src/dictionarymodel.h"
#include "../src/inputparser.h"

class TestInputParser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLoadFile();
    void testWordList();

private:
    InputParser     m_inputParser;
    DictionaryModel m_dictionary;
};
