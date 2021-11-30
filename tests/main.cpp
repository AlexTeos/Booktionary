#include "tst_fileparser.h"
#include "tst_outputgenerator.h"
#include "tst_translator.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TESTLIB_SELFCOVERAGE_START(TestObject)
    TestFileParser      tst_fileparser;
    TestTranslator      tst_translator;
    TestOutputGenerator tst_outputGenerator;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tst_fileparser, argc, argv) or QTest::qExec(&tst_translator, argc, argv) or
           QTest::qExec(&tst_outputGenerator, argc, argv);
}
