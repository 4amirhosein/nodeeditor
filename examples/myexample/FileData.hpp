#pragma once
#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;


class FileData : public NodeData {

public:
    FileData()
    {}
    FileData( QString  &text)
        :_text(text)
    {}
    NodeDataType type () const override
    { return NodeDataType {"text" , "Text"} ; }

    QString file() const {return _text;}


public :
    QString _text;
};
