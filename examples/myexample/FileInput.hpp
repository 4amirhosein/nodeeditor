#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtCore/QEvent>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "FileData.hpp"


#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


class FileInput : public NodeDataModel {
    Q_OBJECT

public:
    FileInput();

    QString
    caption() const override {
        return "Input Text File";
    }

    QString
    name() const  override{
        return "FileInputDataModel";
    }

    unsigned int nPorts(PortType portType) const override ;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

public :
    void setInData(std::shared_ptr<NodeData> NodeData,PortIndex port ) override {}

    std::shared_ptr<NodeData>
    outData(PortIndex port) override ;

    virtual
    QWidget *
    embeddedWidget() { return _label;}


protected :
    bool
    eventFilter(QObject *object, QEvent *event) override;

private :

    QLabel * _label;
    QString _file;


};
