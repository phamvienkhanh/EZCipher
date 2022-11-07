#include "components/NodeAES.h"

NodeAES::NodeAES()
{
    _dataOut = std::make_shared<ByteArray>();

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
            auto cons = SceneMgr::Inst()->getScene()->connections();
            auto it = cons.find(_idConsPortAAD);
            if (it != cons.end()) {
                // TODO: overload function delete connection by uuid
                SceneMgr::Inst()->getScene()->deleteConnection(*(it->second));
            }
        }
    });

    _cbKeySize = new QComboBox(_view);
    _cbKeySize->addItems({Ciphers::KeySizes::_128, Ciphers::KeySizes::_256});

    _cbIsEncrypt = new QComboBox(_view);
    _cbIsEncrypt->addItems({"Encrypt", "Decrypt"});

    _txtDataIn = new QTextEdit(_view);
    _txtDataIn->setPlaceholderText("data");

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
    layout->addWidget(_txtDataIn);
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

QString NodeAES::portCaption(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    if(portType == QtNodes::PortType::Out)
        return QString("");

    switch (portIndex)
    {
    case 0:
        return QString("data");
    
    case 1:
        return QString("key");

    case 2:
        return QString("iv");

    case 3:
        return QString("aad");
    
    default:
        return QString("");
    }
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
            return 3;
        }

        return 3;
    }

    return 0;
}

QtNodes::NodeDataType NodeAES::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}

void NodeAES::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port)
{
    auto data = std::dynamic_pointer_cast<ByteArray>(nodeData);
    switch (port)
    {
    case PortIdx::InData:
        _dataIn = data;
        _txtDataIn->setReadOnly(_dataIn ? true : false);
        break;
    
    case PortIdx::Key:
        _key = data;
        _txtKey->setReadOnly(_key ? true : false);
        break;
    
    case PortIdx::IV:
        _iv = data;
        _txtIV->setReadOnly(_iv ? true : false);
        break;
    
    case PortIdx::AAD:
        _aad = data;        
        break;
    
    default:
        break;
    }

    process();
}

std::shared_ptr<QtNodes::NodeData> NodeAES::outData(QtNodes::PortIndex port)
{
    return _dataOut;
}

void NodeAES::process()
{
    QByteArray dataIn;
    QByteArray key;
    QByteArray iv;
    QByteArray aad;

    if(_dataIn) {
        dataIn = _dataIn->data();
    }
    else {
        dataIn = _txtDataIn->toPlainText().toUtf8();
    }

    if(_key) {
        key = _key->data();
    }
    else {
        key = _txtKey->toPlainText().toUtf8();
    }

    if(_iv) {
        iv = _iv->data();
    }
    else {
        iv = _txtIV->toPlainText().toUtf8();
    }

    if(_aad) {
        aad = _aad->data();
    }
    else {
        // aad = _txtAAD->toPlainText().toUtf8();
    }

    Ciphers::AES::InitParam param;
    param.isEnc = true;
    param.iv = iv;
    param.key = key;
    param.keySize = Ciphers::KeySize::_256;
    param.mode = Ciphers::Mode::CBC;

    QByteArray buff;
    Ciphers::Error error = _aes.init(param);
    if(error != Ciphers::None) {
        _stateValidate = QtNodes::NodeValidationState::Error;

        if(error == Ciphers::InvalidIvSize) {
            _mesgValid = QString("invalid IV size");
        }
        else if(error == Ciphers::InvalidKeySize) {
            _mesgValid = QString("invalid key size");
        }
        else if(error == Ciphers::CreateContextFailed) {
            _mesgValid = QString("create context failed");
        }
        else if(error == Ciphers::InitContextFailed) {
            _mesgValid = QString("init context failed");
        }
        else {
            _mesgValid = QString("failed");
        }
    }
    else {
        _stateValidate = QtNodes::NodeValidationState::Valid;
        buff.append(_aes.update(dataIn));
        buff.append(_aes.final());
    }
    
    _dataOut->reset(buff);

    dataUpdated(0);
}

QtNodes::NodeValidationState NodeAES::validationState() const
{
    return _stateValidate;
}

QString NodeAES::validationMessage() const
{
    return _mesgValid;
}

QWidget* NodeAES::embeddedWidget()
{
    return _view;
}

void NodeAES::inputConnectionCreated(QtNodes::Connection const& connection)
{
    if(connection.getPortIndex(QtNodes::PortType::In) == 2) {
        _idConsPortAAD = connection.id();
    }
}

void NodeAES::inputConnectionDeleted(QtNodes::Connection const& connection)
{
    if(connection.getPortIndex(QtNodes::PortType::In) == 2) {
        _idConsPortAAD = QUuid();
    }
}
