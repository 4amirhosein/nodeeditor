#include <QMessageBox>
#include "FileFactory.hpp"
#include "FileInput.hpp"

FileInput::FileInput()
    : _label(new QLabel("Click here to add file")) , _file(QString(""))
  {
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);
    _label->setMargin(10);
    _label->installEventFilter(this);
}

unsigned int
FileInput::nPorts(QtNodes::PortType portType) const
{
    unsigned int result;
    switch (portType) {
    case PortType::In:
        result = 0;
        break;
    case PortType::Out:
        result = 1;
        break;
    }
    return result;
}

QtNodes::NodeDataType
FileInput::
dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return FileData().type();
}



bool
FileInput::eventFilter(QObject * object , QEvent *event) {

    if(object == _label){
        if(event->type() == QEvent::MouseButtonPress){
            qDebug() << " RUN INPUT EVENT FILTER ";
            QString filename = QFileDialog::getOpenFileName(nullptr,
                                                            tr("Open Text File"),
                                                            QDir::homePath(),
                                                            tr("Text Files (*.txt)"));
            try{
                FileFactory fileFactory;
                _file = * fileFactory.readTextFile(filename);
            }
            catch(std::exception &e){
                qWarning() << e.what();
                return true;
            }
            QFileInfo fileInfo(filename);

            qDebug() << "Input file " << _file;

            _label->setText(fileInfo.fileName() + " Uploaded");
            _label->adjustSize();

            Q_EMIT dataUpdated(0);

            return true;
        }
    }
    return false;
}

std::shared_ptr<QtNodes::NodeData>
FileInput::outData(QtNodes::PortIndex port)
{
    return std::make_shared<FileData>(_file);
}

