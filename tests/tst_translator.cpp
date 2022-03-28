#include "tst_translator.h"

QList<QString> WordsToTranslateS = {"cross",
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
                                    "carefully"};

QList<QString> WordsToTranslateM = {"accustomed",
                                    "agreement",
                                    "apply for",
                                    "be fond of",
                                    "best-selling",
                                    "chamber",
                                    "chaos",
                                    "common",
                                    "contact",
                                    "continent",
                                    "copy",
                                    "countless",
                                    "create",
                                    "deathly",
                                    "decade",
                                    "demanding",
                                    "dominate",
                                    "don't mind",
                                    "doubles",
                                    "downpour",
                                    "due",
                                    "elect",
                                    "enthusiastic",
                                    "eternity",
                                    "euphoria",
                                    "fail",
                                    "fan",
                                    "fancy dress",
                                    "female",
                                    "fine",
                                    "foxhunting",
                                    "gifted",
                                    "goblet",
                                    "ground",
                                    "hallow",
                                    "harmony",
                                    "have a word",
                                    "heated",
                                    "hero",
                                    "horse riding",
                                    "image",
                                    "infectious",
                                    "institute",
                                    "introduce",
                                    "invest",
                                    "launch",
                                    "lifestyle",
                                    "loathe",
                                    "longhand",
                                    "make your mark",
                                    "male",
                                    "measles",
                                    "medieval",
                                    "mob",
                                    "musical",
                                    "myth",
                                    "name",
                                    "numerous",
                                    "obsession",
                                    "once and for all",
                                    "orphan",
                                    "passionate",
                                    "philosopher",
                                    "phoenix",
                                    "poverty",
                                    "producer",
                                    "psychological",
                                    "public school",
                                    "regular",
                                    "resign",
                                    "respond",
                                    "rivalry",
                                    "slow down",
                                    "snap up",
                                    "soccer",
                                    "socialite",
                                    "sort out",
                                    "stage",
                                    "statistics",
                                    "sticking point",
                                    "strike",
                                    "sympathy",
                                    "talent",
                                    "tattoo",
                                    "the big time",
                                    "to the full",
                                    "totally adv",
                                    "track",
                                    "trademark",
                                    "try one's luck",
                                    "twinkly",
                                    "underwear",
                                    "video game",
                                    "violent",
                                    "waste ground",
                                    "wizard",
                                    "accomplish",
                                    "actually",
                                    "amazing",
                                    "ambassador",
                                    "annual",
                                    "attend",
                                    "bake",
                                    "banking",
                                    "bargain",
                                    "be in touch",
                                    "(surf)board",
                                    "boarding school",
                                    "boil",
                                    "broadcaster",
                                    "budget",
                                    "butler",
                                    "buzz",
                                    "cash flow",
                                    "cashier",
                                    "casserole dish",
                                    "catch up on",
                                    "challenging",
                                    "charity",
                                    "charming",
                                    "cheque",
                                    "chop",
                                    "concentrate",
                                    "concerned",
                                    "conservative",
                                    "convenient",
                                    "cope",
                                    "day off",
                                    "decent",
                                    "deputy",
                                    "documentary",
                                    "drill",
                                    "dutiful",
                                    "duty",
                                    "earn a living",
                                    "earner",
                                    "eccentric",
                                    "employee",
                                    "engagement",
                                    "enormous",
                                    "expand",
                                    "extensively",
                                    "extravagantly",
                                    "ferry",
                                    "fly by",
                                    "food processor",
                                    "frustration",
                                    "fry",
                                    "get away from it all",
                                    "goods",
                                    "handyman",
                                    "hardware",
                                    "hard-working",
                                    "head of state",
                                    "heir",
                                    "helmet",
                                    "herb",
                                    "honey",
                                    "host",
                                    "housekeeper",
                                    "huge",
                                    "human resources",
                                    "hunting",
                                    "in charge",
                                    "in response to",
                                    "include",
                                    "inconvenience",
                                    "industry",
                                    "invoice",
                                    "involve",
                                    "keep fit",
                                    "land",
                                    "laptop",
                                    "lavish",
                                    "lifeguard",
                                    "lifetime",
                                    "lively",
                                    "madly",
                                    "maid",
                                    "managing director",
                                    "manufacture",
                                    "meditate",
                                    "memo",
                                    "mild",
                                    "minced meat",
                                    "mix",
                                    "modernize",
                                    "monarch",
                                    "negotiate",
                                    "occupy",
                                    "organic",
                                    "payment",
                                    "peel",
                                    "personnel",
                                    "plant",
                                    "politician",
                                    "porter",
                                    "portray",
                                    "praise",
                                    "product",
                                    "promote",
                                    "qualification",
                                    "racket",
                                    "reception",
                                    "reckon",
                                    "recruit",
                                    "redecorate",
                                    "ridiculous",
                                    "riverside",
                                    "roast",
                                    "sales",
                                    "screwdriver",
                                    "serve an ace",
                                    "service",
                                    "shift",
                                    "shooting",
                                    "situate",
                                    "sketch",
                                    "small talk",
                                    "soap",
                                    "socializer",
                                    "squeeze",
                                    "state",
                                    "stiff",
                                    "support",
                                    "sweat",
                                    "sweetheart",
                                    "tackle",
                                    "tantrum",
                                    "tax",
                                    "tell off",
                                    "term-time",
                                    "throne",
                                    "torch",
                                    "trade",
                                    "training",
                                    "understanding",
                                    "valet",
                                    "VIP",
                                    "weed",
                                    "weigh",
                                    "well intentioned",
                                    "workforce",
                                    "zoom",
                                    "alleyway",
                                    "archaeology",
                                    "area",
                                    "background",
                                    "barrel",
                                    "Basque",
                                    "beat",
                                    "bilingual",
                                    "block",
                                    "brief",
                                    "bright",
                                    "cancellation",
                                    "cherish",
                                    "client",
                                    "close-knit",
                                    "communal",
                                    "community",
                                    "cosmopolitan",
                                    "cracked",
                                    "culture",
                                    "daylight",
                                    "demolition",
                                    "destroy",
                                    "dressmaker",
                                    "earthquake",
                                    "elderly",
                                    "end up",
                                    "equator",
                                    "extended family",
                                    "extinct",
                                    "fee",
                                    "filling",
                                    "for good",
                                    "forbid",
                                    "frail",
                                    "frugally",
                                    "global warming",
                                    "(not) go far",
                                    "go live",
                                    "go on about",
                                    "a great deal",
                                    "headquarters",
                                    "heritage",
                                    "hold",
                                    "hopefully",
                                    "hospitality",
                                    "iceberg",
                                    "immediate family",
                                    "kit",
                                    "life expectancy",
                                    "make",
                                    "means",
                                    "motto",
                                    "muffin",
                                    "municipal",
                                    "neutral",
                                    "nonsense",
                                    "noticeable",
                                    "on the clock",
                                    "operator",
                                    "performance",
                                    "pin number",
                                    "policy",
                                    "preschool",
                                    "prestigious",
                                    "presumably",
                                    "profile",
                                    "propaganda",
                                    "provide",
                                    "pyjamas",
                                    "raise",
                                    "reach",
                                    "regret",
                                    "research",
                                    "rubbish",
                                    "settle down",
                                    "shortly",
                                    "similarity",
                                    "slum",
                                    "storey",
                                    "stressed",
                                    "structure",
                                    "stuck",
                                    "suburb",
                                    "survey",
                                    "take away",
                                    "take home",
                                    "tricky",
                                    "ultimately",
                                    "urgent",
                                    "vote",
                                    "well-balanced",
                                    "widely"

};

const QString ApiKeyFileName = "yandexDictionaryKey.txt";

void TestTranslator::initTestCase()
{
    QVERIFY(m_translator.initialize(ApiKeyFileName));
}

void TestTranslator::cleanupTestCase() {}

void TestTranslator::testTranslateParser()
{
    m_translator.clearCache();

    Word w("cab");
    QVERIFY(m_translator.translate(w));

    QVERIFY(std::distance(w.begin(), w.end()) == 3);

    quint8 presenceFlag = 0;
    for (const auto& definition : w)
    {
        switch (definition.m_pos)
        {
            case PartOfSpeech::Unknown:
                QVERIFY(definition.m_meanings.size() == 1);
                QVERIFY(definition.m_meanings[0] == "CAB");
                QVERIFY(definition.m_examples.size() == 0);
                presenceFlag |= 0x1;
                break;
            case PartOfSpeech::Verb:
                QVERIFY(definition.m_meanings.size() == 1);
                QVERIFY(definition.m_meanings[0] == "ехать на такси");
                QVERIFY(definition.m_examples.size() == 0);
                presenceFlag |= 0x2;
                break;
            case PartOfSpeech::Noun:
                QVERIFY(definition.m_meanings.size() == 7);
                QVERIFY(definition.m_meanings[0] == "кэб");
                QVERIFY(definition.m_meanings[1] == "кабина");
                QVERIFY(definition.m_meanings[2] == "такси");
                QVERIFY(definition.m_meanings[3] == "экипаж");
                QVERIFY(definition.m_meanings[4] == "пролетка");
                QVERIFY(definition.m_meanings[5] == "наемный экипаж");
                QVERIFY(definition.m_meanings[6] == "кабина управления");
                QVERIFY(definition.m_examples.size() == 2);
                QVERIFY(definition.m_examples[0].first == "truck cab");
                QVERIFY(definition.m_examples[0].second == "кабина грузовика");
                QVERIFY(definition.m_examples[1].first == "take a cab");
                QVERIFY(definition.m_examples[1].second == "взять такси");
                presenceFlag |= 0x4;
                break;
            default:
                QFAIL("");
        }
    }

    QVERIFY(presenceFlag == 7);
}

void TestTranslator::testTranslate()
{
    m_translator.clearCache();

    foreach(auto word, WordsToTranslateS)
    {
        Word w(word);
        QVERIFY(m_translator.translate(w));
    }
}

void TestTranslator::testTranslateN()
{
    m_translator.clearCache();

    QList<Word> dictionary;

    foreach(auto word, WordsToTranslateM)
    {
        Word w(word);
        dictionary.push_back(w);
    }

    qsizetype updateCount = 128;

    int modelCounter = 0;
    for (auto iter = dictionary.begin(); iter != dictionary.end(); iter += updateCount, modelCounter += updateCount)
    {
        if (dictionary.size() - modelCounter < updateCount)
        {
            updateCount = dictionary.size() - modelCounter;
        }
        QVERIFY(m_translator.translateNMT(iter, updateCount));
    }

    return;
}
