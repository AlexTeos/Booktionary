#include <QtAlgorithms>
#include <QtTest>

#include "../src/outputgenerator.h"

class TestOutputGenerator : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testGenerateOutput();

private:
    OutputGenerator m_outputGenerator;
};
