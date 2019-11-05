#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtCore/QEvent>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "FileData.hpp"


#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


class FileProcessor : public NodeDataModel {
    Q_OBJECT

public:
    FileProcessor();

    QString
    caption() const override {
        return "Text File Processor";
    }

    QString
    name() const  override{
        return "FileProcessorDataModel";
    }

    unsigned int nPorts(PortType portType) const override ;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

public :
    void setInData(std::shared_ptr<NodeData> NodeData,PortIndex port ) override;

    std::shared_ptr<NodeData>
    outData(PortIndex port) override ;

    virtual
    QWidget *
    embeddedWidget() { return nullptr;}

    NodeValidationState
    validationState() const override;

    QString
    validationMessage() const override;


    void compute();


private :


    std::shared_ptr<NodeData> _nodeData;

    QString _outputFile;
    QString _regex ;

    NodeValidationState modelValidationState = NodeValidationState::Warning;
    QString modelValidationError = QString("Missing or incorrect inputs");

};
