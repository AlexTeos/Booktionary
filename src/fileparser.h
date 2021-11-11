#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>

class FileParser : public QObject
{
    Q_OBJECT
public slots:
    bool loadFile(const QString &fileName, const int readLineSize = 256);

public:
    const QMap<QString, uint32_t>& getWords();
    void reset();

private:
    QMap<QString, uint32_t> words;
};

#endif // MYCLASS_H
