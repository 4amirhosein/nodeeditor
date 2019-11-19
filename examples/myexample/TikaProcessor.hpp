#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtCore/QEvent>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QtWidgets/QLineEdit>
#include <QProcess>
#include <QLabel>
#include "FileData.hpp"


#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


class TikaProcessor : public NodeDataModel {
    Q_OBJECT

public:
    TikaProcessor();

    QString
    caption() const override {
        return "Tika File Processor";
    }

    QString
    name() const  override{
        return "TikaProcessorDataModel";
    }

    unsigned int nPorts(PortType portType) const override ;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

public :
    void setInData(std::shared_ptr<NodeData> NodeData,PortIndex port ) override;

    std::shared_ptr<NodeData>
    outData(PortIndex port) override ;

    virtual
    QWidget *
    embeddedWidget() { return _label;}

    NodeValidationState
    validationState() const override;

    QString
    validationMessage() const override;


    void compute();

protected :
    bool
    eventFilter(QObject *object, QEvent *event) override;

    void setState(QString , NodeValidationState);


private :

    std::shared_ptr<NodeData> _nodeData;
    QString _filePath;
    QProcess * _tikaProcess;
    QString _tikaAppPath;
    QString _outputFile;
    QLabel * _label;
    NodeValidationState modelValidationState = NodeValidationState::Warning;
    QString modelValidationError = QString("Missing file input");

private Q_SLOTS:
    void processFinished();

};
