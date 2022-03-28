#include <QtAlgorithms>
#include <QtTest>

#include "../src/translator.h"

class TestTranslator : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testTranslateParser();
    void testTranslate();
    void testTranslateN();

private:
    Translator m_translator;
};
