#include "adduserdialog.h"

addUserDialog::addUserDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel("用户账号");
    nameEdit = new QLineEdit;
    QLabel *typeLabel = new QLabel("用户类型");
    typeEdit = new QComboBox;
    QStringList typeList;
    typeList<<"管理员"<<"供应商"<<"采购员";
    typeEdit->addItems(typeList);
    QLabel *pwdLabel = new QLabel("密码");
    pwdEdit = new QLineEdit();
    addButton = new QPushButton("添加");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameEdit,0,1);
    layout->addWidget(typeLabel,1,0);
    layout->addWidget(typeEdit,1,1);
    layout->addWidget(pwdLabel,2,0);
    layout->addWidget(pwdEdit,2,1);
    layout->addWidget(addButton,3,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}
