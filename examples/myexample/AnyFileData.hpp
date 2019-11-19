#pragma once
#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;


class AnyFileData : public NodeData {

public:
    AnyFileData()
    {}
    AnyFileData( QString  &filePath)
        :_filePath(filePath)
    {}
    NodeDataType type () const override
    { return NodeDataType {"path" , "Path"} ; }

    QString filePath() const {return _filePath;}


public :
    QString _filePath;
};
