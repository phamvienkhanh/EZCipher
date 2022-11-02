#include "components/NodeEncoder.h"

NodeEncoder::NodeEncoder()
{
    _dataOut = std::make_shared<ByteArray>();
    
    _view = new QWidget;
    _view->setFixedSize({150, 50});
    _view->autoFillBackground();
    QPalette pl;
    pl.setColor(QPalette::ColorRole::Window, Qt::transparent);
    _view->setPalette(pl);

    _cbEncode = new QComboBox(_view);
    _cbEncode->addItem("Hex");
    _cbEncode->addItem("Base64");
    connect(_cbEncode, &QComboBox::currentTextChanged, this, [&](const QString&) {
        encode();
    });

    QVBoxLayout* layout = new QVBoxLayout(_view);
    layout->addWidget(_cbEncode);

    _view->setLayout(layout);
}

QString NodeEncoder::caption() const 
{
    return QString("Encoder");
}

QString NodeEncoder::portCaption(QtNodes::PortType, QtNodes::PortIndex) const
{
    return QString("");
}

QString NodeEncoder::name() const
{
    return QString("encoder");
}

unsigned int NodeEncoder::nPorts(QtNodes::PortType portType) const
{
    return 1;
}

QtNodes::NodeDataType NodeEncoder::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}

void NodeEncoder::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port)
{
    _dataIn = std::dynamic_pointer_cast<ByteArray>(nodeData);
    encode();
}

std::shared_ptr<QtNodes::NodeData> NodeEncoder::outData(QtNodes::PortIndex port)
{
    return _dataOut;
}

QWidget* NodeEncoder::embeddedWidget()
{
    return _view;
}

void NodeEncoder::encode()
{
    if(_dataIn) {
        auto curType = _cbEncode->currentText();

        if(curType == "Hex") {
            _dataOut->reset(_dataIn->toHex().toUtf8());
        }
        else if(curType == "Base64") {
            _dataOut->reset(_dataIn->toBase64().toUtf8());
        }
        else {
            _dataOut->reset(_dataIn->data());
        }
        
        dataUpdated(0);
    }
}

NodeEncoder::~NodeEncoder()
{
    
}

