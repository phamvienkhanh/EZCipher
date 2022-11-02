#ifndef _NODES_TEXT_INPUT_H_
#define _NODES_TEXT_INPUT_H_

#include "precompile.h"

class TextInput: public QtNodes::NodeDataModel
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
    void process();

public:
    TextInput();
    ~TextInput();

private:
    QWidget* _view = nullptr;
    QTextEdit* _textEdit = nullptr;

    SharedPtr<ByteArray> _data = nullptr;
};

#endif