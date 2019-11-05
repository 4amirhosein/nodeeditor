#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtCore/QEvent>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "FileData.hpp"
#include "FileFactory.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;


class FileOutput : public NodeDataModel {
    Q_OBJECT

public:
    FileOutput();

    QString
    caption() const override {
        return "OutPut Result File";
    }

    QString
    name() const  override{
        return "FileOutputDataModel";
    }

    unsigned int nPorts(PortType portType) const override ;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

public :
    void setInData(std::shared_ptr<NodeData> NodeData,PortIndex port ) override;

    std::shared_ptr<NodeData>
    outData(PortIndex port) override;

    virtual
    QWidget *
    embeddedWidget() { return _pushButton;}

protected :
    bool
    eventFilter(QObject *object, QEvent *event) override;




private :

    std::shared_ptr<NodeData> _nodeData;
    QString _file;
    QPushButton * _pushButton;


};
