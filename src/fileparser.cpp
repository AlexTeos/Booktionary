#include "fileparser.h"

#include <QFile>
#include <QMap>
#include <QRegularExpression>
#include <iostream>

bool FileParser::loadFile(const QString& fileName, const int readLineSize)
{
    QFile file(fileName.last(fileName.length() - 8));
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly);
        if (file.isOpen())
        {
            char    data[readLineSize];
            QString line;
            int     read_cont = file.read(data, readLineSize);
            while (read_cont)
            {
                line += QString::fromLocal8Bit(data, read_cont);

                int space = line.indexOf(QRegularExpression("[,. \n\r]"));
                while (space != -1)

                {
                    QString word = line.first(space).toLower();
                    word.remove(QRegularExpression("[^a-z\\-]"));
                    if (word.size())
                        words.contains(word) ? words.insert(word, words.value(word) + 1) : words.insert(word, 1);

                    line.remove(0, space + 1);
                    space = line.indexOf(QRegularExpression("[,. \n\r]"));
                }

                read_cont = file.read(data, readLineSize);
            }
            if (line.length())
            {
                line.remove(QRegularExpression("[^a-z\\-]"));
                if (line.size())
                    words.contains(line) ? words.insert(line, words.value(line) + 1) : words.insert(line, 0);
            }
            return true;
        }
        else
            std::cout << "Can't open file" << std::endl;
    }
    else
        std::cout << "File doesn't exits" << std::endl;

    return false;
}

const QMap<QString, uint32_t>& FileParser::getWords()
{
    return words;
}

void FileParser::reset()
{
    words.clear();
}
