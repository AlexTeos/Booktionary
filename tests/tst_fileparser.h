#include <QtAlgorithms>
#include <QtTest>

#include "../src/fileparser.h"

class TestFileParser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLoadFile();
    void testWordMap();
    void testWordList();

private:
    FileParser fileParser;
};
