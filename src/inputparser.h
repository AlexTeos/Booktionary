#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

#include "dictionarymodel.h"

class InputParser : public QObject
{
    Q_OBJECT
public slots:
    bool loadFile(const QString& fileName, const int readLineSize = 256);

public:
    explicit InputParser();
    explicit InputParser(DictionaryModel* dictiomaryModel);
    void setDictionaryModel(DictionaryModel* newDictionaryModel);

private:
    DictionaryModel* m_dictionaryModel;
};

#endif // MYCLASS_H
