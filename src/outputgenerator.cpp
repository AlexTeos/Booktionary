#include "outputgenerator.h"

#include "QFile"
#include "word.h"

// "word";"перевод"
// "word";"transcription";"перевод"
// "word";"перевод";"example";"перевод"
// "word";"transcription";"перевод";"example";"перевод"

OutputGenerator::OutputGenerator() {}

bool OutputGenerator::generateOutput(const Dictionary& dictionary, const QString& outputFileName)
{
    QFile outputFile(outputFileName);
    if (outputFile.open(QIODevice::WriteOnly))
    {
        foreach(Word word, dictionary)
        {
            foreach(Definition definition, word)
            {
                QString wordLine = "\"" + word.getWord() + "\";\"" + definition.meaning.join(",") + "\"";

                foreach(OriginalAndTranslation example, definition) wordLine +=
                    (";\"" + example.first + "\";\"" + example.second + "\"");

                wordLine += "\n";
                outputFile.write(wordLine.toUtf8());
            }
        }

        outputFile.close();
        return true;
    }

    return false;
}
