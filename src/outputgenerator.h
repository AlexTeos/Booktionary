#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include "dictionarymodel.h"

class OutputGenerator
{
public:
    OutputGenerator();

    bool generateOutput(const DictionaryModel& dictionary, const QString& outputFileName);
};

#endif // OUTPUTGENERATOR_H
