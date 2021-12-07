#include <QtAlgorithms>
#include <QtTest>

#include "../src/inputparser.h"

class TestInputParser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLoadFile();
    void testWordMap();
    void testWordList();

private:
    InputParser inputParser;
};
