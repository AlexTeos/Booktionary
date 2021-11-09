#include <QtTest>

#include "../src/fileparser.h"

QString testText1 = "Wikipedia (/ˌwɪkɪˈpiːdiə/ (About this soundlisten) wik-ih-PEE-dee-ə or /ˌwɪki-/ (About this soundlisten) wik-ee-) is a free content, multilingual online encyclopedia written and maintained by a community of volunteers through a model of open collaboration, using a wiki-based editing system. Individual contributors, also called editors, are known as Wikipedians. It is the largest and most-read reference work in history,[3] and consistently one of the 15 most popular websites ranked by Alexa; as of 2021, Wikipedia was ranked the 13th most popular site.[3][4] A visitor spends an average time on Wikipedia of 3 minutes and 45 seconds each day.[5] It is hosted by the Wikimedia Foundation, an American non-profit organization funded mainly through small donations.[6]"
                    "Wikipedia was launched on January 15, 2001, by Jimmy Wales[7] and Larry Sanger; Sanger coined its name as a blending of \"wiki\" and \"encyclopedia\".[8][9] Initially available only in English, versions in other languages were quickly developed. Its combined editions comprise more than 57 million articles, attracting around 2 billion unique device visits per month, and more than 17 million edits per month (1.9 edits per second).[10][11] In 2006, Time magazine stated that the policy of allowing anyone to edit had made Wikipedia the \"biggest (and perhaps best) encyclopedia in the world\", and is \"a testament to the vision of one man, Jimmy Wales\".[12]"
                    "Wikipedia has received praise for its enablement of the democratization of knowledge, extent of coverage, unique structure, culture, and reduced amount of commercial bias, but criticism for exhibiting systemic bias, particularly gender bias against women and alleged ideological bias.[13][14] Its reliability was frequently criticized in the 2000s, but has improved over time and has been generally praised in the late 2010s and early 2020s.[3][13][15] Its coverage of controversial topics such as American politics and major events such as the COVID-19 pandemic has received substantial media attention. It has been censored by world governments, ranging from specific pages to the entire site. It has become an element of popular culture, with references in books, films and academic studies. In 2018, Facebook and YouTube announced that they would help users detect fake news by suggesting fact-checking links to related Wikipedia articles.[16][17]";

class TestFileParser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLoadFile();

private:
    FileParser fileParser;
    QFile testTextFile1;
};

void TestFileParser::initTestCase()
{
    testTextFile1.setFileName("testTextFile1.txt");
    testTextFile1.open(QIODevice::WriteOnly);
    QVERIFY(testTextFile1.isOpen());
    QVERIFY(testTextFile1.write(testText1.toLocal8Bit()) == testText1.toLocal8Bit().length());
    QVERIFY(testTextFile1.write(testText1.toLocal8Bit()) == testText1.toLocal8Bit().length());
    testTextFile1.close();
}

void TestFileParser::cleanupTestCase()
{
    testTextFile1.remove();
}

void TestFileParser::testLoadFile()
{
    QVERIFY("file:///" + fileParser.loadFile(testTextFile1.fileName()));
}

#include "tst_fileparser.moc"

QTEST_APPLESS_MAIN(TestFileParser)

