#include "components/TextView.h"

TextView::TextView()
{
    _view = new QWidget;
    _view->setFixedSize({150, 50});
    _view->autoFillBackground();
    QPalette pl;
    pl.setColor(QPalette::ColorRole::Window, Qt::transparent);
    _view->setPalette(pl);

    _txtData = new QTextEdit(_view);
    _txtData->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout(_view);
    layout->addWidget(_txtData);

    _view->setLayout(layout);
}

TextView::~TextView()
{
}

QString TextView::caption() const 
{
    return QString("Text view");
}

QString TextView::portCaption(QtNodes::PortType type, QtNodes::PortIndex) const 
{ 
    return QString("");
}

QString TextView::name() const
{
    return QString("Text view");
}

unsigned int TextView::nPorts(QtNodes::PortType portType) const
{
    switch (portType)
    {
    case QtNodes::PortType::In:
        return 1;
    
    default:
        return 0;
    }
}

QtNodes::NodeDataType TextView::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}

void TextView::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port)
{
    _data = std::dynamic_pointer_cast<ByteArray>(nodeData);
    if(_view && _data) {        
        updateView();
    }
}

void TextView::updateView()
{
    if(_data) {       
        _txtData->setPlainText(_data->toString());
        _view->adjustSize();
    }
}

std::shared_ptr<QtNodes::NodeData> TextView::outData(QtNodes::PortIndex port)
{
    return _data;
}

QWidget* TextView::embeddedWidget()
{
    return _view;
}