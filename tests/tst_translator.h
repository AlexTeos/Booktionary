#include <QtAlgorithms>
#include <QtTest>

#include "../src/translator.h"

class TestTranslator : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testTranslate();

private:
    Translator translator;
};
