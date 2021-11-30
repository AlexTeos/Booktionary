#ifndef OUTPUTGENERATOR_H
#define OUTPUTGENERATOR_H

#include "dictionary.h"

class OutputGenerator
{
public:
    OutputGenerator();

    bool generateOutput(const Dictionary& dictionary, const QString& outputFileName);
};

#endif // OUTPUTGENERATOR_H
