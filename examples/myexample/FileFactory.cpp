#include "FileFactory.hpp"
FileFactory::FileFactory()
{

}

void FileFactory::writeTextFile(QString filename , std::shared_ptr<QString> textSharedPointer )
{
    if(filename.isEmpty())
        throw std::invalid_argument(" FileFactory.writeTextFile :: File path is empty  ");

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
     throw std::invalid_argument(" FileFactory.writeTextFile :: can not open file ");

    QTextStream out(&file);
    out << * textSharedPointer;
    file.flush();
    file.close();

}

std::shared_ptr<QString> FileFactory::readTextFile(QString filename)
{
    if(filename.isEmpty())
        throw std::invalid_argument(" FileFactory.readTextFile :: File path is empty ");

    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        file.close();
        throw std::invalid_argument(" FileFactory.readTextFile :: File is not Readble or is not text ");
    }
    QTextStream in(&file);

    std::shared_ptr<QString> fileText = std::make_shared<QString>(in.readAll());

    file.close();

    return fileText;
}

