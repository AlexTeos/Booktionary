#ifndef MYCLASS_H
#define MYCLASS_H

#include <QList>
#include <QMap>
#include <QObject>

class InputParser : public QObject
{
    Q_OBJECT
public slots:
    bool loadFile(const QString& fileName, const int readLineSize = 256);

public:
    QList<QString>                 getWordList();
    const QMap<QString, uint32_t>& getWords();
    void                           reset();

private:
    QMap<QString, uint32_t> words;
};

#endif // MYCLASS_H
