#include "components/TextInput.h"

TextInput::TextInput()
{
    _data = std::make_shared<ByteArray>();

    _view = new QWidget;
    _view->setFixedSize({150, 50});
    _view->autoFillBackground();
    QPalette pl;
    pl.setColor(QPalette::ColorRole::Window, Qt::transparent);
    _view->setPalette(pl);

    _textEdit = new QTextEdit(_view);
    _textEdit->setText("");
    connect(_textEdit, &QTextEdit::textChanged, this, [&](){
        process();
    });

    QVBoxLayout* layout = new QVBoxLayout(_view);
    layout->addWidget(_textEdit);

    _view->setLayout(layout);
}

TextInput::~TextInput()
{
}

QString TextInput::caption() const 
{
    return QString("Text input");
}

QString TextInput::portCaption(QtNodes::PortType, QtNodes::PortIndex) const 
{ 
    return QString("");
}

QString TextInput::name() const
{
    return QString("Text input");
}

unsigned int TextInput::nPorts(QtNodes::PortType portType) const
{
    switch (portType)
    {
    case QtNodes::PortType::Out:
        return 1;
    
    default:
        return 0;
    }
}

QtNodes::NodeDataType TextInput::dataType(QtNodes::PortType, QtNodes::PortIndex) const
{
    return ByteArray().type();
}

void TextInput::setInData(std::shared_ptr<QtNodes::NodeData> , QtNodes::PortIndex )
{

}

std::shared_ptr<QtNodes::NodeData> TextInput::outData(QtNodes::PortIndex port)
{
    return _data;
}

QWidget* TextInput::embeddedWidget()
{
    return _view;
}

void TextInput::process()
{
    _data->fromString(_textEdit->toPlainText());
    dataUpdated(0);
}