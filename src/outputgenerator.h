#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include <QObject>

#include "dictionarymodel.h"

class OutputGenerator : public QObject
{
    Q_OBJECT
public:
    explicit OutputGenerator();
    explicit OutputGenerator(DictionaryModel* dictiomaryModel);
    void setDictionaryModel(DictionaryModel* newDictionaryModel);

public slots:
    bool generateOutput(const QString& outputFileName);

private:
    DictionaryModel* m_dictionaryModel;
};

#endif // OUTPUTGENERATOR_H
