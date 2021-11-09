#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>

class FileParser : public QObject
{
    Q_OBJECT
public slots:
    bool loadFile(const QString &fileName);
};

#endif // MYCLASS_H
