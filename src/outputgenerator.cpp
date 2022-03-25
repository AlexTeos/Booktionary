#include "outputgenerator.h"

#include "QFile"
#include "word.h"

// "word";"перевод"
// "word";"transcription";"перевод"
// "word";"перевод";"example";"перевод"
// "word";"transcription";"перевод";"example";"перевод"

OutputGenerator::OutputGenerator() : m_dictionaryModel(nullptr) {}

OutputGenerator::OutputGenerator(DictionaryModel* dictiomaryModel) : m_dictionaryModel(dictiomaryModel) {}

void OutputGenerator::setDictionaryModel(DictionaryModel* newDictionaryModel)
{
    m_dictionaryModel = newDictionaryModel;
}

bool OutputGenerator::generateOutput(const QString& outputFileName,
                                     const bool&    mostFrequentMeaning,
                                     const bool&    onlyWithExamples)
{
    if (m_dictionaryModel != nullptr)
    {
        QFile outputFile(outputFileName.last(outputFileName.length() - 8));
        if (outputFile.open(QIODevice::WriteOnly))
        {
            for (const auto& word : *m_dictionaryModel)
            {
                foreach(Definition definition, word)
                {
                    if (onlyWithExamples && not definition.m_examples.count()) continue;

                    QString wordLine = "\"" + word.word() + "\";\"" + definition.m_meanings.join(",") + "\"";

                    foreach(OriginalAndTranslation example, definition) wordLine +=
                        (";\"" + example.first + "\";\"" + example.second + "\"");

                    wordLine += "\n";
                    outputFile.write(wordLine.toUtf8());

                    if (mostFrequentMeaning) break;
                }
            }

            outputFile.close();
            return true;
        }
    }

    return false;
}
