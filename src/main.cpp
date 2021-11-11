#include <QDebug>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>

#include "fileparser.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* item = engine.rootObjects().first();

    FileParser fileParser;
    QObject::connect(item, SIGNAL(loadFile(QString)), &fileParser, SLOT(loadFile(QString)));

    return app.exec();
}
