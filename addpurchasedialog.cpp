#include "addpurchasedialog.h"

addPurchaseDialog::addPurchaseDialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *layout = new QGridLayout;
    QVBoxLayout *m_layout = new QVBoxLayout;

    scrollArea = new QScrollArea();
    scrollAreaWidgetContents = new QWidget();
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollAreaWidgetContents);

    scrollArea->setWidget(scrollAreaWidgetContents);
    scrollArea->setWidgetResizable(true);
    // 添加一个占位的垂直布局，用于添加新的水平布局
    scrollAreaLayout->addStretch();

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

    layout->addWidget(userLabel, 0, 0);
    layout->addWidget(user, 0, 1);
    layout->addWidget(supplierLabel, 1, 0);
    layout->addWidget(supplier, 1, 1);

    // 添加复选框和数量输入框
    QString sql3 = QString("select med_name from med;");
    queryModel->setQuery(sql3);
    rowCount = queryModel->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QString medName = queryModel->data(queryModel->index(row, 0)).toString();
        QCheckBox *checkBox = new QCheckBox(medName);

        connect(checkBox, &QCheckBox::stateChanged, this, &addPurchaseDialog::onCheckBoxStateChanged);
        QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(scrollAreaWidgetContents->layout());
        if (layout) {
            // 将复选框添加到垂直布局中
            layout->insertWidget(layout->count() - 1, checkBox);
        }
    }
    m_layout->addLayout(layout);
    m_layout->addWidget(scrollArea);

    // 添加确定按钮
    addButton = new QPushButton("添加");
    m_layout->addWidget(addButton);

    setLayout(m_layout);
}

void addPurchaseDialog::onCheckBoxStateChanged(int state) {
    QCheckBox *checkBox = qobject_cast<QCheckBox*>(sender());
    if (checkBox) {
        // 获取药品名称
        QString medicineName = checkBox->text();

        // 如果药品被选中，创建相应的输入框
        if (state == Qt::Checked) {
            QLineEdit *quantityLineEdit = new QLineEdit(this);
            quantityLineEdit->setPlaceholderText("数量");
            medicineQuantityMap[checkBox] = quantityLineEdit;

            QHBoxLayout *medicineLayout = new QHBoxLayout;
            medicineLayout->addWidget(checkBox);
//            medicineLayout->addWidget(new QLabel(medicineName, this));
//            medicineLayout->addWidget(new QLabel("数量:", this));  // 添加数量标签
            medicineLayout->addWidget(quantityLineEdit);

            // 将水平布局添加到垂直布局
            QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(scrollAreaWidgetContents->layout());
            if (layout) {
                layout->insertLayout(layout->count() - 1, medicineLayout);
            }
        } else {
            // 如果药品被取消选择，删除相应的输入框
            QLineEdit *quantityLineEdit = medicineQuantityMap.value(checkBox);
            if (quantityLineEdit) {
                delete quantityLineEdit;
                medicineQuantityMap.remove(checkBox);
            }
        }
    }
}
