#include "components/NodeDecoder.h"

NodeDecoder::NodeDecoder()
{
    _dataOut = std::make_shared<ByteArray>();
    
    _view = new QWidget;
    _view->setFixedSize({150, 50});
    _view->autoFillBackground();
    QPalette pl;
    pl.setColor(QPalette::ColorRole::Window, Qt::transparent);
    _view->setPalette(pl);

    _cbDecode = new QComboBox(_view);
    _cbDecode->addItem("Hex");
    _cbDecode->addItem("Base64");
    connect(_cbDecode, &QComboBox::currentTextChanged, this, [&](const QString&) {
        decode();
    });

    QVBoxLayout* layout = new QVBoxLayout(_view);
    layout->addWidget(_cbDecode);

    _view->setLayout(layout);
}

QString NodeDecoder::caption() const 
{
    return QString("Decoder");
}

QString NodeDecoder::portCaption(QtNodes::PortType, QtNodes::PortIndex) const
{
    return QString("");
}

QString NodeDecoder::name() const
{
    return QString("decoder");
}

unsigned int NodeDecoder::nPorts(QtNodes::PortType portType) const
{
    return 1;
}

QtNodes::NodeDataType NodeDecoder::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}

void NodeDecoder::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port)
{
    _dataIn = std::dynamic_pointer_cast<ByteArray>(nodeData);
    decode();
}

std::shared_ptr<QtNodes::NodeData> NodeDecoder::outData(QtNodes::PortIndex port)
{
    return _dataOut;
}

QWidget* NodeDecoder::embeddedWidget()
{
    return _view;
}

void NodeDecoder::decode()
{
    if(_dataIn) {
        auto curType = _cbDecode->currentText();

        if(curType == "Hex") {
            _dataOut->fromHex(_dataIn->toString());
        }
        else if(curType == "Base64") {
            _dataOut->fromBase64(_dataIn->toString());
        }
        else {
            _dataOut->reset(_dataIn->data());
        }
        
        dataUpdated(0);
    }
}

NodeDecoder::~NodeDecoder()
{
    
}