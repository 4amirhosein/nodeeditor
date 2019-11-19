#include "AnyFileInput.hpp"

#include "FileData.hpp"

AnyFileInput::AnyFileInput() : _label(new QLabel("Click here to add file")) , _path(QString("")) {
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);
    _label->setMargin(10);
    _label->installEventFilter(this);

}

unsigned int AnyFileInput::nPorts(QtNodes::PortType portType) const
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

QtNodes::NodeDataType AnyFileInput::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return AnyFileData().type();
}


std::shared_ptr<QtNodes::NodeData> AnyFileInput::outData(QtNodes::PortIndex port)
{
    return std::make_shared<AnyFileData>(_path);
}

bool AnyFileInput::eventFilter(QObject *object, QEvent *event)
{
    if(object == _label){
        if(event->type() == QEvent::MouseButtonPress){
            qDebug() << " RUN INPUT EVENT FILTER ";
            QString filename = QFileDialog::getOpenFileName(nullptr,
                                                            tr("Open Any File"),
                                                            QDir::homePath(),
                                                            tr("Any File (*.*)"));
            if (!filename.isEmpty()) {
                QFileInfo fileInfo(filename);
                _label->setText(fileInfo.fileName() + " Path Saved");
                _label->adjustSize();
                _path = filename;

                Q_EMIT dataUpdated(0);
            }
            return true;
        }
    }
    return false;
}

