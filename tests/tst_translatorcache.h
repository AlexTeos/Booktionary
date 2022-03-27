#include <QtAlgorithms>
#include <QtTest>

#include "../src/translator.h"

class TestTranslatorCache : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testAll();
};
