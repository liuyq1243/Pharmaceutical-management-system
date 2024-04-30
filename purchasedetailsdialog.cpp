#include "purchasedetailsdialog.h"

purchaseDetailsDialog::purchaseDetailsDialog(QWidget *parent)
    : QDialog(parent)
{
    // 设置采购单详细信息
    QGridLayout* grid = new QGridLayout;
    QLabel *labelOrderNumber = new QLabel("采购单号: ");
    orderID = new QLabel();
    QLabel *labelPurchaser = new QLabel("采购人员: ");
    user = new QLabel();
    QLabel *labelSupplier = new QLabel("供应商: ");
    supplier = new QLabel();
    QLabel *labelPurchaseDate = new QLabel("采购日期: ");
    date = new QLabel();
    QLabel *labelTotalPrice = new QLabel("总价格: ");
    price = new QLabel();
    QLabel *labelOrderStatus = new QLabel("采购单状态: ");
    status = new QLabel();
    grid->addWidget(labelOrderNumber, 0, 0);
    grid->addWidget(orderID, 0, 1);
    grid->addWidget(labelPurchaser, 1, 0);
    grid->addWidget(user, 1, 1);
    grid->addWidget(labelSupplier, 2, 0);
    grid->addWidget(supplier, 2, 1);
    grid->addWidget(labelPurchaseDate, 3, 0);
    grid->addWidget(date, 3, 1);
    grid->addWidget(labelTotalPrice, 4, 0);
    grid->addWidget(price, 4, 1);
    grid->addWidget(labelOrderStatus, 5, 0);
    grid->addWidget(status, 5, 1);

    // 创建一个滚动区域，并添加药品信息
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollWidget = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);

    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(grid);
    mainLayout->addWidget(scrollArea);

    btn_pass = new QPushButton("通过");
    btn_reject = new QPushButton("拒绝");
    QHBoxLayout* btns = new QHBoxLayout;

    QLabel *labelMedicineInfo = new QLabel(QString("药品%1: 类型 - %2, 单价 - $10.50").arg("黄葵胶囊").arg("妇科用药"));
    scrollLayout->addWidget(labelMedicineInfo);
    QLabel *labelMedicineInfo2 = new QLabel(QString("药品%1: 类型 - %2, 单价 - $39.9").arg("碧凯（保妇康栓）").arg("妇科用药"));
    scrollLayout->addWidget(labelMedicineInfo2);
    scrollArea->setLayout(scrollLayout);

    btns->addWidget(btn_pass);
    btns->addWidget(btn_reject);
    mainLayout->addLayout(btns);

    setLayout(mainLayout);
    setWindowTitle("采购单详情");
}

purchaseDetailsDialog::~purchaseDetailsDialog(){}
