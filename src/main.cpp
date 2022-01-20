#include <QDebug>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dictionarymodel.h"
#include "inputparser.h"
#include "outputgenerator.h"
#include "translator.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    DictionaryModel       dictionaryModel;

    engine.rootContext()->setContextProperty("dictionaryModel", &dictionaryModel);

    InputParser inputParser(&dictionaryModel);
    engine.rootContext()->setContextProperty("inputParser", &inputParser);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    return app.exec();
}
