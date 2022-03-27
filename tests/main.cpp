#include "tst_inputparser.h"
#include "tst_outputgenerator.h"
#include "tst_translator.h"
#include "tst_translatorcache.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TESTLIB_SELFCOVERAGE_START(TestObject)
    TestInputParser     tst_inputparser;
    TestTranslator      tst_translator;
    TestOutputGenerator tst_outputGenerator;
    TestTranslatorCache tst_translatorCache;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tst_inputparser, argc, argv) or QTest::qExec(&tst_outputGenerator, argc, argv) or
           QTest::qExec(&tst_translatorCache, argc, argv) or QTest::qExec(&tst_translator, argc, argv);
}
