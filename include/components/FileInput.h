#ifndef _NODES_FILE_INPUT_
#define _NODES_FILE_INPUT_

#include "precompile.h"

class FileInput: public QtNodes::NodeDataModel
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
    FileInput();
    ~FileInput();

private:
    std::shared_ptr<ByteArray> _data = nullptr;
    QString _fileSelected;

    QFileDialog _fileDialog;
    QWidget* _view = nullptr;
    QLabel* _lblFileName = nullptr;
};

#endif