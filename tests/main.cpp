#include "tst_inputparser.h"
#include "tst_outputgenerator.h"
#include "tst_translator.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TESTLIB_SELFCOVERAGE_START(TestObject)
    TestInputParser     tst_inputparser;
    TestTranslator      tst_translator;
    TestOutputGenerator tst_outputGenerator;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tst_inputparser, argc, argv) or QTest::qExec(&tst_translator, argc, argv) or
           QTest::qExec(&tst_outputGenerator, argc, argv);
}
