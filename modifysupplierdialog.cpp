#include "modifysupplierdialog.h"
#include <QGridLayout>

modifySupplierDialog::modifySupplierDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel("供应商名称");
    nameEdit = new QLineEdit;
    QLabel *addrLabel = new QLabel("商家所在地");
    addrEdit = new QComboBox;
    QStringList addrList;
    addrList<<"北京"<<"上海"<<"陕西"<<"深圳"<<"四川";
    addrEdit->addItems(addrList);
    QLabel *contactLabel = new QLabel("联系人");
    contactEdit = new QLineEdit;
    QLabel *teleLabel = new QLabel("联系方式");
    teleEdit = new QLineEdit;
    modifyButton = new QPushButton("修改");
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameEdit,0,1);
    layout->addWidget(addrLabel,1,0);
    layout->addWidget(addrEdit,1,1);
    layout->addWidget(contactLabel,2,0);
    layout->addWidget(contactEdit,2,1);
    layout->addWidget(teleLabel,3,0);
    layout->addWidget(teleEdit,3,1);
    layout->addWidget(modifyButton,4,1);
    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}
modifySupplierDialog::~modifySupplierDialog()
{
}
