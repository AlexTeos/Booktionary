#include "inputparser.h"

#include <QFile>
#include <QRegularExpression>
#include <QSet>

InputParser::InputParser() : m_dictionaryModel(nullptr) {}

InputParser::InputParser(DictionaryModel* dictiomaryModel) : m_dictionaryModel(dictiomaryModel) {}

bool InputParser::loadFile(const QString& fileName, const int readLineSize)
{
    if (m_dictionaryModel != nullptr)
    {
        QFile file(fileName.last(fileName.length() - 8));
        if (file.exists())
        {
            file.open(QIODevice::ReadOnly);
            if (file.isOpen())
            {
                QSet<QString> words;
                char          data[readLineSize];
                QString       line;
                int           read_cont = file.read(data, readLineSize);
                while (read_cont)
                {
                    line += QString::fromLocal8Bit(data, read_cont);

                    int space = line.indexOf(QRegularExpression("[,. \n\r]"));
                    while (space != -1)

                    {
                        QString word = line.first(space).toLower();
                        word.remove(QRegularExpression("[^a-z\\-]"));
                        if (word.size())
                        {
                            if (not words.contains(word))
                            {
                                words.insert(word);
                                m_dictionaryModel->addWord(word);
                            }
                        }

                        line.remove(0, space + 1);
                        space = line.indexOf(QRegularExpression("[,. \n\r]"));
                    }

                    read_cont = file.read(data, readLineSize);
                }
                if (line.length())
                {
                    line.remove(QRegularExpression("[^a-z\\-]"));
                    if (line.size())
                    {
                        if (not words.contains(line))
                        {
                            words.insert(line);
                            m_dictionaryModel->addWord(line);
                        }
                    }
                }

                return true;
            }
            else
                qWarning() << "Can't open file";
        }
        else
            qWarning() << "File doesn't exist";
    }
    else
        qCritical() << "Dictionary isn't set";

    return false;
}

void InputParser::setDictionaryModel(DictionaryModel* newDictionaryModel)
{
    m_dictionaryModel = newDictionaryModel;
}
