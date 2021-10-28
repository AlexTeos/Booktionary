#include "fileparser.h"
#include <QFile>
#include <QRegularExpression>
#include <iostream>
#include <set>

void FileParser::loadFile(const QString &fileName)
{
    QFile file(fileName.last(fileName.length()-8));
    std::set<QString> words;
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
                    words.insert(word);

                    line.remove(0, space + 1);
                    space = line.indexOf(" ");
                }
            }
            if(line.length())
            {
                line.remove(QRegularExpression("[^a-z\\-]"));
                words.insert(line);
            }
            std::cout << "Done" << std::endl;
        }
        else
            std::cout << "Can't open file" << std::endl;
    }
    else
        std::cout << "File doesn't exits" << std::endl;
}
