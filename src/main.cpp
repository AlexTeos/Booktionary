#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QDebug>
#include "fileparser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *item = engine.rootObjects().first();

    FileParser fileParser;
    QObject::connect(item, SIGNAL(loadFile(QString)),
                     &fileParser, SLOT(loadFile(QString)));

    return app.exec();
}
