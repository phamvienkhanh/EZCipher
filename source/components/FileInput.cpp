#include "components/FileInput.h"

FileInput::FileInput()
{
    _data = std::make_shared<ByteArray>();

    _fileDialog.setFileMode(QFileDialog::ExistingFile);

    _view = new QWidget;
    QPalette pl;
    pl.setColor(QPalette::ColorRole::Window, Qt::transparent);
    _view->setPalette(pl);

    QVBoxLayout* layout = new QVBoxLayout(_view);

    _lblFileName = new QLabel(_view);
    _lblFileName->setText(_fileSelected);

    QPushButton* btnOpen = new QPushButton(_view);
    btnOpen->setText("Open");
    connect(btnOpen, &QPushButton::clicked, this, [&](bool checked){
        if(_fileDialog.exec()) {
            _fileSelected = _fileDialog.selectedFiles().value(0);
            process();
        }
    });    

    layout->addWidget(btnOpen);
    layout->addWidget(_lblFileName, 1);

    _view->setLayout(layout);
}

FileInput::~FileInput()
{

}

void FileInput::process()
{
    QFileInfo fileInfo(_fileSelected);
    _lblFileName->setText(fileInfo.fileName());
    _lblFileName->adjustSize();

    _data->fromFile(_fileSelected);
    
    dataUpdated(0);
}

QString FileInput::caption() const
{
    return QString("File input");
}

QString FileInput::portCaption(QtNodes::PortType, QtNodes::PortIndex) const
{
    return QString("");
}

QString FileInput::name() const
{
    return QString("File input");
}

unsigned int FileInput::nPorts(QtNodes::PortType portType) const
{
    return 1;
}

QtNodes::NodeDataType FileInput::dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const
{
    return ByteArray().type();
}


void FileInput::setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port)
{

}

std::shared_ptr<QtNodes::NodeData> FileInput::outData(QtNodes::PortIndex port)
{
    return _data;
}

QWidget* FileInput::embeddedWidget()
{
    return _view;
}
