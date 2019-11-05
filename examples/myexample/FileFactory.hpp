#pragma once

#include <QFile>
#include <QTextStream>
#include <memory>
#include <QDir>
#include <QFileInfo>
#include "FileData.hpp"

class FileFactory {


public :
    FileFactory();
//    FileFactory(QString filename) { setFileName(filename); }
    void writeTextFile(QString filename, std::shared_ptr<QString> textSharedPointer);
    std::shared_ptr<QString> readTextFile(QString filename);
//    void setFileName(QString filename);
//    QString getFileName();

//private :
//    QString _filename;

};
