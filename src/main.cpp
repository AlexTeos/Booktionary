#include <QDebug>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>

#include "dictionary.h"
#include "inputparser.h"
#include "outputgenerator.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* item = engine.rootObjects().first();

    InputParser inputParser;
    QObject::connect(item, SIGNAL(loadFile(QString)), &inputParser, SLOT(loadFile(QString)));
    Dictionary dictionary(inputParser.getWordList());

    return app.exec();
}
