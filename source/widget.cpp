#include "widget.h"

#include <QVBoxLayout>

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
#include <nodes/FlowView>

#include "components/TextInput.h"
#include "components/TextView.h"
#include "components/NodeEncoder.h"
#include "components/NodeDecoder.h"
#include "components/NodeCompare.h"
#include "components/FileInput.h"
#include "components/NodeAES.h"

static std::shared_ptr<QtNodes::DataModelRegistry> registerDataModels() {
    auto ret = std::make_shared<QtNodes::DataModelRegistry>();

    ret->registerModel<TextInput>("Input");
    ret->registerModel<FileInput>("Input");

    ret->registerModel<TextView>("Output");

    ret->registerModel<NodeEncoder>("Converts");
    ret->registerModel<NodeDecoder>("Converts");

    ret->registerModel<NodeCompare>("Compare");

    ret->registerModel<NodeAES>("Ciphers");
    
    return ret;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    auto scene = new QtNodes::FlowScene(registerDataModels(), this);
    l->addWidget(new QtNodes::FlowView(scene));
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);

    QPushButton* btnSave = new QPushButton(this);
    btnSave->setText("save");
    connect(btnSave, &QPushButton::clicked, this, [scene](bool checked){
        scene->save();
    });

    QPushButton* btnLoad = new QPushButton(this);
    btnLoad->setText("load");
    btnLoad->setGeometry(btnSave->x() + btnLoad->width() + 10, btnSave->y(), btnLoad->width(), btnLoad->height());
    connect(btnLoad, &QPushButton::clicked, this, [scene](bool checked){
        scene->load();
    });

}

Widget::~Widget()
{
}

