#include "components/NodeCompare.h"

NodeCompare::NodeCompare()
{
    _out = std::make_shared<ByteArray>();

    _cbType = new QComboBox;
    _cbType->addItems({">", "<", ">=", "<=", "=", "!="});
    connect(_cbType, &QComboBox::currentTextChanged, this, [&](const QString&){
        process();
    });
}

NodeCompare::~NodeCompare()
{

}

QString NodeCompare::caption() const 
{
    return QString("Compare");
}

QString NodeCompare::portCaption(QtNodes::PortType, QtNodes::PortIndex) const
{
    return QString("");
}

QString NodeCompare::name() const
{
    return QString("Compare");
}

unsigned int NodeCompare::nPorts(QtNodes::PortType portType) const
{
    return portType == QtNodes::PortType::In ? 2 : 1;
}

QtNodes::NodeDataType NodeCompare::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}

void NodeCompare::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port) 
{
    switch (port)
    {
    case 0:
        _left = std::dynamic_pointer_cast<ByteArray>(nodeData);
        break;
    case 1:
        _right = std::dynamic_pointer_cast<ByteArray>(nodeData);
        break;
    default:
        break;
    }

    process();
}

void NodeCompare::process()
{
    if(_left && _right) {
        QString curType = _cbType->currentText();
        bool isTrue = false;
        
        if(curType == ">") {
            if(_left->data() > _right->data()) {
                isTrue = true;
            }
        }
        else if(curType == ">=") {
            if(_left->data() >= _right->data()) {
                isTrue = true;
            }
        }
        else if(curType == "<") {
            if(_left->data() < _right->data()) {
                isTrue = true;
            }
        }
        else if(curType == "<=") {
            if(_left->data() <= _right->data()) {
                isTrue = true;
            }
        }
        else if(curType == "=") {
            if(_left->data() == _right->data()) {
                isTrue = true;
            }
        }
        else if(curType == "!=") {
            if(_left->data() != _right->data()) {
                isTrue = true;
            }
        }

        if(isTrue) {
            _out->fromString("True");
        }
        else {
            _out->fromString("False");
        }        
    }
    else {
        _out->fromString("None");
    }

    dataUpdated(0);
}

std::shared_ptr<QtNodes::NodeData> NodeCompare::outData(QtNodes::PortIndex port) 
{
    return _out;
}

QWidget* NodeCompare::embeddedWidget() 
{
    return _cbType;
}

