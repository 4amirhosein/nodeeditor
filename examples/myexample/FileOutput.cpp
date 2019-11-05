#include "FileOutput.hpp"
FileOutput::FileOutput()
    : _pushButton(new QPushButton("Click for saving")) ,
      _file(QString(""))
{

    _pushButton->installEventFilter(this);
}

unsigned int FileOutput::nPorts(QtNodes::PortType portType) const
{
    unsigned int result;
    switch (portType) {
    case PortType::In:
        result = 1;
        break;
    case PortType::Out:
        result = 0;
        break;
    }
    return result;
}

QtNodes::NodeDataType FileOutput::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return FileData().type();
}

void FileOutput::setInData(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex port)
{
    _nodeData = data;
    if(_nodeData){
        auto d = std::dynamic_pointer_cast<FileData>(_nodeData);
        _file = d->file();
    }
}

std::shared_ptr<QtNodes::NodeData> FileOutput::outData(QtNodes::PortIndex port) {
    return _nodeData;
}


bool
FileOutput::eventFilter(QObject *object, QEvent *event ){

    if (object == _pushButton) {
        if ( event->type() == QEvent::MouseButtonPress ){

            if (!_nodeData) {
                qDebug() << "FileOutput.eventFilter ::  _nodeData in null ";
                QMessageBox::warning(nullptr, tr("My Application"),
                                               tr("There is no input to save.\n"),
                                               QMessageBox::Ok );
                return true;
            }

            qDebug() << " RUN OUTPUT EVENT FILTER";
            QString fileName = QFileDialog::getSaveFileName(nullptr,
                tr("Save Address Book"), QDir::homePath()+ "/result.txt",
                tr("Address Book (*.abk)All Files (*)"));
            std::shared_ptr<FileData> fileData = std::dynamic_pointer_cast<FileData>(_nodeData);
            std::shared_ptr<QString> textFile = std::make_shared<QString>(fileData->file());
            try {

                FileFactory fileFactory;
                fileFactory.writeTextFile(fileName , textFile);

            } catch(std::exception &e ){
                qDebug() << e.what();
                return true ;
            }
        }
    }
    return false ;
}
