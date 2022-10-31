#include "components/NodeAES.h"

NodeAES::NodeAES()
{
    _data = std::make_shared<ByteArray>();

    Ciphers::AES::InitParam param;
    param.isEnc = true;
    param.iv = QByteArray(16, '\0');
    param.key = QByteArray(32, 'a');
    param.mode = Ciphers::Mode::CBC;

    QByteArray buff;
    _aes.init(param);
    buff.append(_aes.update("123456"));
    buff.append(_aes.final());

    _data->reset(buff);
}

NodeAES::~NodeAES()
{

}

QString NodeAES::caption() const
{
    return QString("");
}

QString NodeAES::portCaption(QtNodes::PortType, QtNodes::PortIndex) const
{
    return QString("");
}

QString NodeAES::name() const
{
    return QString("AES");
}

unsigned int NodeAES::nPorts(QtNodes::PortType portType) const
{
    return 1;
}

QtNodes::NodeDataType NodeAES::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}

void NodeAES::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port)
{

}

std::shared_ptr<QtNodes::NodeData> NodeAES::outData(QtNodes::PortIndex port)
{
    return _data;
}

QWidget* NodeAES::embeddedWidget()
{
    return nullptr;
}
