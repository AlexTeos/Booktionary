#include "fileparser.h"
#include <QFile>
#include <QRegularExpression>
#include <iostream>
#include <QMap>

bool FileParser::loadFile(const QString &fileName)
{
    QFile file(fileName.last(fileName.length()-8));
    QMap<QString, uint32_t> words;
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        if(file.isOpen()){

            char data[16];
            QString line;
            while(file.read(data, 16)){
                line += QString::fromLocal8Bit(data);

                int space = line.indexOf(" ");
                while(space != -1)
                {
                    QString word = line.first(space).toLower();
                    word.remove(QRegularExpression("[^a-z\\-]"));
                    words.contains(word) ? words.insert(word, words.value(word)+1) : words.insert(word, 1);

                    line.remove(0, space + 1);
                    space = line.indexOf(" ");
                }
            }
            if(line.length())
            {
                line.remove(QRegularExpression("[^a-z\\-]"));
                words.contains(line) ? words.insert(line, words.value(line)+1) : words.insert(line, 0);
            }
            std::cout << "Done" << std::endl;
            return true;
        }
        else
            std::cout << "Can't open file" << std::endl;
    }
    else
        std::cout << "File doesn't exits" << std::endl;

    return false;
}

