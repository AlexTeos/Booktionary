#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>

class FileParser : public QObject
{
    Q_OBJECT
public slots:
    void loadFile(const QString &fileName);
};

#endif // MYCLASS_H
