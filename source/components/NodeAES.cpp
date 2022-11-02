#include "components/NodeAES.h"

NodeAES::NodeAES()
{
    // _data = std::make_shared<ByteArray>();

    // Ciphers::AES::InitParam param;
    // param.isEnc = true;
    // param.iv = QByteArray(16, '\0');
    // param.key = QByteArray(32, 'a');
    // param.mode = Ciphers::Mode::CBC;

    // QByteArray buff;
    // _aes.init(param);
    // buff.append(_aes.update("123456"));
    // buff.append(_aes.final());

    // _data->reset(buff);

    _view = new QWidget;
    _view->setFixedSize({220, 150});
    _view->autoFillBackground();
    QPalette pl;
    pl.setColor(QPalette::ColorRole::Window, Qt::transparent);
    _view->setPalette(pl);

    _cbMode = new QComboBox(_view);
    _cbMode->addItems({Ciphers::Modes::ECB, Ciphers::Modes::CBC, Ciphers::Modes::GCM});
    connect(_cbMode, &QComboBox::currentTextChanged, this, [&](const QString& curMode) {
        if(curMode == Ciphers::Modes::GCM) {
            portAdded();
        }
        else {
            portRemoved();
        }
    });

    _cbKeySize = new QComboBox(_view);
    _cbKeySize->addItems({Ciphers::KeySizes::_128, Ciphers::KeySizes::_256});

    _cbIsEncrypt = new QComboBox(_view);
    _cbIsEncrypt->addItems({"Encrypt", "Decrypt"});

    _txtKey = new QTextEdit(_view);
    _txtKey->setPlaceholderText("key");

    _txtIV = new QTextEdit(_view);
    _txtIV->setPlaceholderText("IV");

    QWidget* group = new QWidget(_view);
    QHBoxLayout* hlayout = new QHBoxLayout(_view);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(_cbKeySize);
    hlayout->addWidget(_cbMode);
    hlayout->addWidget(_cbIsEncrypt);
    group->setLayout(hlayout);

    QVBoxLayout* layout = new QVBoxLayout(_view);
    layout->addWidget(group);
    layout->addWidget(_txtKey);
    layout->addWidget(_txtIV);

    _view->setLayout(layout);
}

NodeAES::~NodeAES()
{

}

QString NodeAES::caption() const
{
    return QString("AES");
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
    if(portType == QtNodes::PortType::Out)
        return 1;

    if(portType == QtNodes::PortType::In) {
        auto curMode = _cbMode->currentText();
        if(curMode == Ciphers::Modes::GCM) {
            return 2;
        }

        return 1;
    }

    return 0;
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
    return _view;
}
