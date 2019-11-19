#pragma once

#include <QObject>
#include <QLabel>
#include <QEvent>
#include <nodes/NodeDataModel>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include "AnyFileData.hpp"
#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;
using QtNodes::NodeDataType;

class AnyFileInput : public NodeDataModel {
public:
    AnyFileInput();

    QString
    caption() const override {
        return "Input Any File";
    }

    QString
    name() const  override{
        return "AnyFileInputDataModel";
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
    QString _path;


};
