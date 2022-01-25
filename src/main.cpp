#include <QDebug>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dictionarymodel.h"
#include "inputparser.h"
#include "outputgenerator.h"
#include "translator.h"

const QString ApiKeyFileName = "yandexDictionaryKey.txt";

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Translator            translator;
    translator.initialize(ApiKeyFileName);
    DictionaryModel dictionaryModel;
    dictionaryModel.setTranslator(&translator);
    InputParser     inputParser(&dictionaryModel);
    OutputGenerator outputGenerator(&dictionaryModel);

    engine.rootContext()->setContextProperty("dictionaryModel", &dictionaryModel);
    engine.rootContext()->setContextProperty("inputParser", &inputParser);
    engine.rootContext()->setContextProperty("outputGenerator", &outputGenerator);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    return app.exec();
}
