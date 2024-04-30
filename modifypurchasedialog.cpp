#include "modifypurchasedialog.h"
#include <QGridLayout>


modifyPurchaseDialog::modifyPurchaseDialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *layout = new QGridLayout;

    QSqlQueryModel* queryModel = new QSqlQueryModel();
//    QList<QString> userList;
//    QList<QString> supplierList;
    user = new QComboBox();
    supplier = new QComboBox();

    QLabel* userLabel = new QLabel();
    userLabel->setText("采购人员");
    //QCombox添加用户
    QString sql1 = QString("select user_name from user;");
    queryModel->setQuery(sql1);
    int rowCount = queryModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // 获取当前行的 QString 数据并存入 QList
        QString userName = queryModel->data(queryModel->index(row, 0)).toString();
        user->addItem(userName);
    }

    QLabel* supplierLabel = new QLabel();
    supplierLabel->setText("供应商");
    //QCombox添加供应商
    QString sql2 = QString("select supplier_name from supplier;");
    queryModel->setQuery(sql2);
    rowCount = queryModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // 获取当前行的 QString 数据并存入 QList
        QString supplierName = queryModel->data(queryModel->index(row, 0)).toString();
        supplier->addItem(supplierName);
    }

    QLabel* dateLabel = new QLabel("日期");
    date = new QLabel();
    QLabel* priceLabel = new QLabel("总价格");
    total_price = new QLabel();
    QLabel* statusLabel = new QLabel("状态");
    status = new QLabel();

    modifyButton = new QPushButton("修改");

    layout->addWidget(userLabel, 0, 0);
    layout->addWidget(user, 0, 1);
    layout->addWidget(supplierLabel, 1, 0);
    layout->addWidget(supplier, 1, 1);
    layout->addWidget(dateLabel, 2, 0);
    layout->addWidget(date, 2, 1);
    layout->addWidget(priceLabel, 3, 0);
    layout->addWidget(total_price, 3, 1);
    layout->addWidget(statusLabel, 4, 0);
    layout->addWidget(status, 4, 1);
    layout->addWidget(modifyButton, 5, 1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}

modifyPurchaseDialog::~modifyPurchaseDialog(){

}
