#pragma once


#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


class ImageLoaderModel : public NodeDataModel
{
    Q_OBJECT
public:
    ImageLoaderModel() {}


};
