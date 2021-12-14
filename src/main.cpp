#include <QDebug>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dictionary.h"
#include "inputparser.h"
#include "outputgenerator.h"
#include "translator.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    QObject* item = engine.rootObjects().first();

    InputParser inputParser;
    engine.rootContext()->setContextProperty("inputParser", &inputParser);
    Dictionary dictionary(inputParser.getWordList());

    return app.exec();
}
