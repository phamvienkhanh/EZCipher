#ifndef _NODES_AES_H_
#define _NODES_AES_H_

#include "precompile.h"

#include "ciphers/AES.h"

class NodeAES: public QtNodes::NodeDataModel
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

    QtNodes::NodeValidationState validationState() const;
    QString validationMessage() const;

    void inputConnectionCreated(QtNodes::Connection const&);
    void inputConnectionDeleted(QtNodes::Connection const&);

private:
    struct PortIdx
    {
        static const int InData = 0;
        static const int Key = 1;
        static const int IV = 2;
        static const int AAD = 3;
    };

private:
    void process();

private:
    Ciphers::AES _aes;
    SharedPtr<ByteArray> _dataIn = nullptr;
    SharedPtr<ByteArray> _dataOut = nullptr;
    SharedPtr<ByteArray> _key = nullptr;
    SharedPtr<ByteArray> _iv = nullptr;
    SharedPtr<ByteArray> _aad = nullptr;

    QWidget* _view = nullptr;
    QComboBox* _cbMode = nullptr;
    QComboBox* _cbIsEncrypt = nullptr;
    QComboBox* _cbKeySize = nullptr;
    QTextEdit* _txtDataIn = nullptr;
    QTextEdit* _txtKey = nullptr;
    QTextEdit* _txtIV = nullptr;

    QUuid _idConsPortAAD;

    QString _mesgValid;
    QtNodes::NodeValidationState _stateValidate = QtNodes::NodeValidationState::Valid;

public:
    NodeAES();
    ~NodeAES();
};

#endif