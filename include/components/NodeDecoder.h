#ifndef _COMPONENTS_NODE_DECODER_
#define _COMPONENTS_NODE_DECODER_

#include "precompile.h"

class NodeDecoder: public QtNodes::NodeDataModel
{

public:
    bool resizable() const { return true; }
    QString caption() const override;
    bool captionVisible() const override { return true; }
    QString portCaption(QtNodes::PortType, QtNodes::PortIndex) const;
    bool portCaptionVisible(QtNodes::PortType, QtNodes::PortIndex) const override { return true; }
    QString name() const;
    unsigned int nPorts(QtNodes::PortType portType) const override;
    QtNodes::NodeDataType dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const override;

    void setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port) override;
    std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port) override;
    QWidget* embeddedWidget() override;

private:
    void decode();

public:
    NodeDecoder();
    ~NodeDecoder();

private:
    QWidget* _view = nullptr;
    QComboBox* _cbDecode = nullptr;

    SharedPtr<ByteArray> _dataIn = nullptr;
    SharedPtr<ByteArray> _dataOut = nullptr;
};

#endif