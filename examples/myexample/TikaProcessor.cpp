#include "TikaProcessor.hpp"
#include "FileData.hpp"
#include "AnyFileData.hpp"
#include <QDebug>


TikaProcessor::TikaProcessor(): _label(new QLabel("Click here to add tika app")) ,
    _tikaAppPath(QString("")),
    _outputFile(QString("")),
    _tikaProcess(new QProcess(this)),
    _filePath(QString(""))
{
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);
    _label->setMargin(10);
    _label->installEventFilter(this);

    connect( _tikaProcess,
             static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
             this,
             &TikaProcessor::processFinished );

}

unsigned int TikaProcessor::nPorts(QtNodes::PortType portType) const
{
    unsigned int result;
    switch (portType) {
    case PortType::In:
        result = 1;
        break;
    case PortType::Out:
        result = 1;
        break;
    }
    return result;
}


QtNodes::NodeDataType TikaProcessor::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    if ( portType == QtNodes::PortType::Out ) {
        return FileData().type();
    }
    else if ( portType == QtNodes::PortType::In ) {
        return AnyFileData().type();
    }
}

void TikaProcessor::setInData(std::shared_ptr<QtNodes::NodeData> NodeData, QtNodes::PortIndex port)
{
    _nodeData = NodeData;

    qDebug() << this->name() << ":: setInData " ;
    if(_nodeData){

        qDebug() << this->name() << ":: setInData " << " NodeData Exist";
        auto d = std::dynamic_pointer_cast<AnyFileData>(_nodeData);

        if  ( d && !d->filePath().isEmpty() ){
            qDebug() << this->name() << ":: setInData " << " d Exist and is valid";
            _filePath = d->filePath();
            compute();
        }
    } else {

    }



//    Q_EMIT dataUpdated(0);
}

std::shared_ptr<QtNodes::NodeData> TikaProcessor::outData(QtNodes::PortIndex port)
{
    return std::make_shared<FileData>(_outputFile);
}

QtNodes::NodeValidationState TikaProcessor::validationState() const
{
    return modelValidationState;
}

QString TikaProcessor::validationMessage() const
{
    return modelValidationError;
}

void TikaProcessor::compute()
{

    if(_tikaAppPath.isEmpty())
        return ;
    qDebug() << this->name() << ":: compute" ;
    QString exec = "java";
    QStringList params;
    params << "-jar" << _tikaAppPath << _filePath;
    qDebug() << this->name() << ":: compute" << exec << params;
    _tikaProcess->start(exec, params);


   setState("Processing", NodeValidationState::Warning );
}

bool TikaProcessor::eventFilter(QObject *object, QEvent *event)
{
    if( object == _label ){
        if(event->type() == QEvent::MouseButtonPress ){
            qDebug() << this->name() << ":: eventFilter" << " Event Accepted" ;
            QString filename = QFileDialog::getOpenFileName(nullptr,
                                                            tr("Open Tika App"),
                                                            QDir::homePath(),
                                                            tr("Jar File (*.jar)"));
            if(!filename.isEmpty()){
                _label->setText(filename + " Selected" );
                _tikaAppPath = filename;
                qDebug() << _tikaAppPath;
            } else {
                setState(" Path is Empty" , NodeValidationState::Warning );
            }
            return true;
        }
    }
    return false;
}

void TikaProcessor::setState(QString message , NodeValidationState state)
{
    this->modelValidationState = state;
    this->modelValidationError = message;
}

void TikaProcessor::processFinished()
{
    qDebug() << this->name() << ":: processFinished ";

    QString output(_tikaProcess->readAllStandardOutput());
    QString error(_tikaProcess->readAllStandardError());

    qDebug() << this->name() << ":: processFinished :: OUTPUT" << output;
    qDebug() << this->name() << ":: processFinished :: ERROR" << error;

    _outputFile = output;

    setState("Porcessing finished", NodeValidationState::Valid);

    Q_EMIT dataUpdated(0);

}

