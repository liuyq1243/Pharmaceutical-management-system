#include "addsupplierdialog.h"
#include <QGridLayout>

addSupplierDialog::addSupplierDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel("供应商名称");
    nameEdit = new QLineEdit;
    QLabel *addrLabel = new QLabel("供应商所在地");
    addrEdit = new QComboBox;
    QStringList addrList;
    addrList<<"陕西"<<"上海"<<"北京"<<"深圳"<<"重庆";
    addrEdit->addItems(addrList);
    QLabel *contactLabel = new QLabel("联系人");
    contactEdit = new QLineEdit;
    QLabel *teleLabel = new QLabel("联系方式");
    teleEdit = new QLineEdit;
    addButton = new QPushButton("添加");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameEdit,0,1);
    layout->addWidget(addrLabel,1,0);
    layout->addWidget(addrEdit,1,1);
    layout->addWidget(contactLabel,2,0);
    layout->addWidget(contactEdit,2,1);
    layout->addWidget(teleLabel,3,0);
    layout->addWidget(teleEdit,3,1);
    layout->addWidget(addButton,4,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}
