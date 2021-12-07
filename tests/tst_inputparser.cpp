#include "tst_inputparser.h"

QVector<QPair<QString, QString>> testTexts = {
    {"wikipedia",
     "Wikipedia (/ˌwɪkɪˈpiːdiə/ (About this soundlisten) wik-ih-PEE-dee-ə or /ˌwɪki-/ (About this soundlisten) "
     "wik-ee-) is a free content, multilingual online encyclopedia written and maintained by a community of volunteers "
     "through a model of open collaboration, using a wiki-based editing system. Individual contributors, also called "
     "editors, are known as Wikipedians."
     "It is the largest and most-read reference work in history,[3] and consistently one of the 15 most popular "
     "websites ranked by Alexa; as of 2021, Wikipedia was ranked the 13th most popular site.[3][4] A visitor spends an "
     "average time on Wikipedia of 3 minutes and 45 seconds each day.[5] It is hosted by the Wikimedia Foundation, an "
     "American non-profit organization funded mainly through small donations.[6]"
     "Wikipedia was launched on January 15, 2001, by Jimmy Wales[7] and Larry Sanger; Sanger coined its name as a "
     "blending of \"wiki\" and \"encyclopedia\".[8][9] Initially available only in English, versions in other "
     "languages were quickly developed. Its combined editions comprise more than 57 million articles, attracting "
     "around 2 billion unique device visits per month,"
     "and more than 17 million edits per month (1.9 edits per second).[10][11] In 2006, Time magazine stated that the "
     "policy of allowing anyone to edit had made Wikipedia the \"biggest (and perhaps best) encyclopedia in the "
     "world\", and is \"a testament to the vision of one man, Jimmy Wales\".[12]"
     "Wikipedia has received praise for its enablement of the democratization of knowledge, extent of coverage, unique "
     "structure, culture, and reduced amount of commercial bias, but criticism for exhibiting systemic bias, "
     "particularly gender bias against women and alleged ideological bias.[13][14] Its reliability was frequently "
     "criticized in the 2000s,"
     "but has improved over time and has been generally praised in the late 2010s and early 2020s.[3][13][15] Its "
     "coverage of controversial topics such as American politics and major events such as the COVID-19 pandemic has "
     "received substantial media attention. It has been censored by world governments, ranging from specific pages to "
     "the entire site."
     "It has become an element of popular culture, with references in books, films and academic studies. In 2018, "
     "Facebook and YouTube announced that they would help users detect fake news by suggesting fact-checking links to "
     "related Wikipedia articles.[16][17]"},
    {"cross",
     ".,.,If   ,./,/.   you.must.cross,a,course~.~cross ~~~~ cow-cow \r\n across\" \"a crowded  cow-cow635 "
     "345crossing, cross4645.3466the cross coarse\n\n\r\n\r\n\r\n\r\n\r\ncow#%@%.{}{},>across.>#%#%>>>..%#the*#@*&% "
     "crowded cow [[[]]]}crossing{{ }}}carefully."}};

QMap<QString, uint32_t> crossTextWordMap = {{"cross", 4},
                                            {"cow", 2},
                                            {"cow-cow", 2},
                                            {"a", 2},
                                            {"across", 2},
                                            {"crowded", 2},
                                            {"crossing", 2},
                                            {"the", 2},
                                            {"if", 1},
                                            {"you", 1},
                                            {"must", 1},
                                            {"course", 1},
                                            {"coarse", 1},
                                            {"carefully", 1}};

QList<QString> crossTextWordList = {
    "cross",
    "cow",
    "cow-cow",
    "a",
    "across",
    "crowded",
    "crossing",
    "the",
    "if",
    "you",
    "must",
    "course",
    "coarse",
    "carefully",
};

void TestInputParser::initTestCase()
{
    foreach(auto testText, testTexts)
    {
        QFile testFile;
        testFile.setFileName(testText.first);
        testFile.open(QIODevice::WriteOnly);
        QVERIFY(testFile.isOpen());
        QVERIFY(testFile.write(testText.second.toLocal8Bit()) == testText.second.toLocal8Bit().length());
        testFile.close();
    }
}

void TestInputParser::cleanupTestCase()
{
    foreach(auto testText, testTexts)
    {
        QFile testFile;
        testFile.setFileName(testText.first);
        testFile.remove();
    }
}

void TestInputParser::testLoadFile()
{
    QVector<uint32_t> testValues = {1024, 16, 3};
    QString           fileName   = "file:///" + testTexts[0].first;
    foreach(auto testValue, testValues)
    {
        QVERIFY(inputParser.loadFile(fileName, testValue));
        inputParser.reset();
    }
}

bool isEqual(const QMap<QString, uint32_t>& map1, const QMap<QString, uint32_t>& map2)
{
    QMap<QString, uint32_t> map2Tmp(map2);
    foreach(auto map1Key, map1.keys())
    {
        if (map2Tmp.value(map1Key, 0) != map1.value(map1Key))
            return false;
        else
            map2Tmp.remove(map1Key);
    }

    return map2.size();
}

bool isEqual(const QList<QString>& list1, const QList<QString>& list2)
{
    if (list1.length() != list1.length()) return false;

    QList<QString> tempList1(list1);
    QList<QString> tempList2(list2);

    std::sort(tempList1.begin(), tempList1.end());
    std::sort(tempList2.begin(), tempList2.end());

    auto list2Iter = tempList2.begin();
    foreach(auto list1Value, tempList1)
    {
        if (list1Value != *list2Iter) return false;
        ++list2Iter;
    }

    return true;
}

void TestInputParser::testWordMap()
{
    QVector<uint32_t> testValues = {512, 24, 5};
    QString           fileName   = "file:///" + testTexts[1].first;
    foreach(auto testValue, testValues)
    {
        QVERIFY(inputParser.loadFile(fileName, testValue));
        QVERIFY(isEqual(inputParser.getWords(), crossTextWordMap));
        inputParser.reset();
    }
}

void TestInputParser::testWordList()
{
    QVector<uint32_t> testValues = {768, 33, 7};
    QString           fileName   = "file:///" + testTexts[1].first;
    foreach(auto testValue, testValues)
    {
        QVERIFY(inputParser.loadFile(fileName, testValue));
        QVERIFY(isEqual(inputParser.getWordList(), crossTextWordList));
        inputParser.reset();
    }
}
