#include "FileProcessor.hpp"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

FileProcessor::FileProcessor() :
    _outputFile(QString("")) ,
    _lineEdit(new QLineEdit()) ,
    _regex(QString("([-+]?)([\\d]{1,2})(((\\.)(\\d+)(,)))(\\s*)(([-+]?)([\\d]{1,3})((\\.)(\\d+))?)"))
{
    connect(_lineEdit,
            &QLineEdit::textChanged,
            this,
            &FileProcessor::onTextEdited);

    _lineEdit->setText(_regex);
    _lineEdit->setMaximumSize(_lineEdit->sizeHint());
}

unsigned int FileProcessor::nPorts(QtNodes::PortType portType) const
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

QtNodes::NodeDataType
FileProcessor::dataType
(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{

    return FileData().type();
}

void
FileProcessor::setInData
(std::shared_ptr<QtNodes::NodeData> data, QtNodes::PortIndex port) {

    _nodeData = data;

    if(_nodeData){

        auto d = std::dynamic_pointer_cast<FileData>(_nodeData);
        if  ( d && !d->file().isEmpty()){
            modelValidationState  = NodeValidationState::Valid;
            modelValidationError =  QString();
            compute();
        } else {
            modelValidationState = NodeValidationState::Warning;
            modelValidationError = QStringLiteral("Missing or incorrect inputs");
        }
    }

    Q_EMIT dataUpdated(0);
}

std::shared_ptr<QtNodes::NodeData> FileProcessor::outData(QtNodes::PortIndex port)
{
    return std::make_shared<FileData>(_outputFile);
}

QtNodes::NodeValidationState FileProcessor::validationState() const
{
    return modelValidationState;
}

QString FileProcessor::validationMessage() const
{
    return modelValidationError;
}

void FileProcessor::onTextEdited(const QString &string)
{
    qDebug() << string;

    _regex = string;

    // for run compute function again :: explicitly calling them does'nt work
    setInData(_nodeData, 0);

    Q_EMIT dataUpdated(0);
}

void FileProcessor::compute()
{
    qDebug() << "RUN COMPUTE EVENT FILTER " ;

    auto d = std::dynamic_pointer_cast<FileData>(_nodeData);

    _outputFile = "" ;

    QRegularExpression re(_regex);

    QRegularExpressionMatchIterator itr = re.globalMatch(d->file());

    while( itr.hasNext() )
    {
        QRegularExpressionMatch match = itr.next();

        _outputFile.append( "Matched regex expresssion found at : " );
        _outputFile.append( QString::number(match.capturedStart()) + " index to ");
        _outputFile.append( QString::number(match.capturedEnd()) + " index ").append("\n");
        _outputFile.append( "And The expression is : " + match.capturedTexts()[0]).append("\n");
    }
    if( _outputFile.isEmpty() ){
        _outputFile.append(" No Matched regex found in this file ");
    }
}
