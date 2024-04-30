#include "purchase.h"
#include "ui_purchase.h"

purchase::purchase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase)
{
    ui->setupUi(this);

    purchaseModel_query = new QSqlQueryModel();
    purchaseModel = new QSqlTableModel();
    purchaseModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交

    purchaseTableView = ui->tableView;

    QString sql_all = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id;");
    purchaseModel_query->setQuery(sql_all);

    //第三列显示
    // 创建委托
    delegate = new MyDelegatePurchase(this);
    // 将委托应用到QTableView上，第三列为 userType 列
    ui->tableView->setItemDelegateForColumn(5, delegate);

    ui->tableView->setModel(purchaseModel_query);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    purchaseModel_query->setHeaderData(0,Qt::Horizontal, "采购单编号");
    purchaseModel_query->setHeaderData(1,Qt::Horizontal, "采购人员");
    purchaseModel_query->setHeaderData(2,Qt::Horizontal, "供应商名称");
    purchaseModel_query->setHeaderData(3,Qt::Horizontal, "采购单日期");
    purchaseModel_query->setHeaderData(4,Qt::Horizontal, "总价格");
    purchaseModel_query->setHeaderData(5,Qt::Horizontal, "采购单状态");

    //返回index
    connect(ui->btn_back, &QPushButton::clicked, this, [&]{
        index* index_page = new index();
        this->close();
        index_page->show();
    });

    //增加
    connect(ui->btn_add, &QPushButton::clicked, this, &purchase::addOrder);

    //查询
    connect(ui->btn_search, &QPushButton::clicked, this, [&]{
        QString orderID = ui->orderID_input->text();
        QString userName = ui->userName_input->text();
        QDate date = ui->orderDate->date();
        QString formatDate = date.toString("yyyy-MM-dd");
        QString sql;

        //如果订单编号输入框非空
        if(!ui->orderID_input->text().isEmpty()){
            sql = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id where order.order_id = %1;")
                    .arg(orderID);
        }else if(!ui->userName_input->text().isEmpty()){
            sql = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id where user.user_name like '%%%1%%';")
                    .arg(userName);
        }else{
            sql = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id where order.order_date = '%1';")
                    .arg(formatDate);
        }

        qDebug() << sql;
        purchaseModel_query->setQuery(sql);
        ui->tableView->setModel(purchaseModel_query);

        purchaseModel_query->setHeaderData(0,Qt::Horizontal, "采购单编号");
        purchaseModel_query->setHeaderData(1,Qt::Horizontal, "采购人员");
        purchaseModel_query->setHeaderData(2,Qt::Horizontal, "供应商名称");
        purchaseModel_query->setHeaderData(3,Qt::Horizontal, "采购单日期");
        purchaseModel_query->setHeaderData(4,Qt::Horizontal, "总价格");
        purchaseModel_query->setHeaderData(5,Qt::Horizontal, "采购单状态");
    });

    //修改
    connect(ui->btn_modify, &QPushButton::clicked, this, &purchase::modifyOrder);

    //删除
    connect(ui->btn_del, &QPushButton::clicked, this, &purchase::deleteOrderData);

    //重置
    connect(ui->btn_reset, &QPushButton::clicked, this, [&]{
        ui->userName_input->clear();
        ui->orderID_input->clear();
        ui->orderDate->clear();

        //更新视图
        QString sql_all = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id;");
        purchaseModel_query->setQuery(sql_all);
        ui->tableView->setModel(purchaseModel_query);
    });

    //查看详情
    connect(ui->btn_more, &QPushButton::clicked, this, &purchase::seeMore);
}

purchase::~purchase()
{
    delete ui;
}

void purchase::seeMore(){
    int curRow = ui->tableView->currentIndex().row();
    detailsDialog = new purchaseDetailsDialog();
    QString sql_all = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id;");
    purchaseModel_query->setQuery(sql_all);
    QVariant data[6];
    for(int i=0;i<6;i++){
        QModelIndex index = purchaseModel_query->index(0, i);
        data[i] = purchaseModel_query->data(index);
    }

    detailsDialog->orderID->setText(data[0].toString());
    detailsDialog->user->setText(data[1].toString());
    detailsDialog->supplier->setText(data[2].toString());
    detailsDialog->date->setText(data[3].toString());
    detailsDialog->price->setText(QString::number(data[4].toDouble(), 'f', 2));
    if(data[5].toInt() == 0){
        detailsDialog->status->setText("未审批");
    }else if(data[5].toInt() == 1){
        detailsDialog->status->setText("通过");
    }else{
        detailsDialog->status->setText("拒绝");
    }

//    QString sql = QString("select med.med_name, med.med_type, med.med_spec, med.med_price from `order` JOIN order_items on `order`.order_id = order_items.order_id JOIN med on med.med_id = order_items.med_id where `order`.order_id = %1;")
//            .arg(curRow);
//    purchaseModel_query->setQuery(sql);
//    qDebug() << "Query execution failed: " << purchaseModel_query->lastError().text();

//    // 创建一个包含药品信息的 QWidget
//    QWidget* widget = new QWidget;
//    QVBoxLayout *layout = new QVBoxLayout(widget);
//    // 遍历查询结果并添加到布局中
//    int rowCount = purchaseModel_query->rowCount();
//    for (int row = 0; row < rowCount; ++row) {
//        QModelIndex index = purchaseModel_query->index(row, 0);
//        QVariant medNameV = purchaseModel_query->data(index);
//        QString medName = medNameV.toString();

//        index = purchaseModel_query->index(row, 1);
//        QVariant medTypeV = purchaseModel_query->data(index);
//        QString medType = medTypeV.toString();

//        index = purchaseModel_query->index(row, 2);
//        QVariant medSpecV = purchaseModel_query->data(index);
//        QString medSpec = medSpecV.toString();


//        index = purchaseModel_query->index(row, 3);
//        QVariant priceV = purchaseModel_query->data(index);
//        double medPrice = priceV.toDouble();

//        // 创建标签显示药品信息
//        QLabel *label = new QLabel(QString("%1 - %2 - %3 - $%4").arg(medName).arg(medType).arg(medSpec)
//                                   .arg(medPrice));
//        layout->addWidget(label);
//    }
//    detailsDialog->scrollArea->setWidget(widget);


    detailsDialog->show();

    connect(detailsDialog->btn_pass, &QPushButton::clicked, this, [&]{
        QMessageBox::information(this, "提示", "通过!");
    });

    connect(detailsDialog->btn_reject, &QPushButton::clicked, this, [&]{
        QMessageBox::information(this, "提示", "拒绝!");
    });
}

void purchase::addOrder(){
    purchaseDialog = new addPurchaseDialog();
    purchaseDialog->show();
    connect(purchaseDialog->addButton,&QPushButton::clicked,this,&purchase::insertOrderData);
}

void purchase::insertOrderData(){
    int user = purchaseDialog->user->currentIndex()+1;
    int supplier = purchaseDialog->supplier->currentIndex();
    QDate currentDate = QDateTime::currentDateTime().date();
    QString orderDate = currentDate.toString("yyyy.MM.dd");

    //获取选择药品信息
    QMap<QString, int> selectedMedicines;
    for (const auto &medicine : (purchaseDialog->medicineQuantityMap).keys()) {
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(medicine);
        if (checkBox && checkBox->isChecked()) {
            QLineEdit *quantityLineEdit = (purchaseDialog->medicineQuantityMap).value(checkBox);
            if (quantityLineEdit) {
                QString medicineName = checkBox->text();
                int quantity = quantityLineEdit->text().toInt();
                selectedMedicines[medicineName] = quantity;
            }
        }
    }
    qDebug() << selectedMedicines.size() << " " << selectedMedicines.firstKey() << selectedMedicines.first();

    int med_nums = selectedMedicines.size();
    int med_id[med_nums];
    int med_amount[med_nums];
    double med_price[med_nums];
    double totalPrice = 0; //总价格
    // 使用迭代器遍历 QMap
    int n = 0;
    QMap<QString, int>::const_iterator i = selectedMedicines.constBegin();
    while (i != selectedMedicines.constEnd()) {
        QString med_name = i.key();
        QString sql = QString("select med_price,med_id from med where med_name = '%1';").arg(med_name);
        purchaseModel_query->setQuery(sql);
        query = purchaseModel_query->query();
        // 执行查询
        if (query.exec()) {
            // 处理查询结果
            while (query.next()) {
                // 获取每一行的数据
                double price = query.value(0).toDouble()*i.value();
                med_id[n] = query.value(1).toInt();
                med_amount[n] = i.value();
                med_price[n] = query.value(0).toDouble();
                n++;
                totalPrice+=price;
            }
        } else {
            // 处理查询失败的情况
            qDebug() << "Query failed: " << query.lastError().text();
        }

        ++i;
    }

    qDebug() <<"user" << user << "supplier" << supplier  << "orderDate" << orderDate << "totalPrice" << totalPrice;

    purchaseModel->setTable("order");
    QSqlRecord record = purchaseModel->record();
    record.setValue(1,user);
    record.setValue(2,supplier);
    record.setValue(3,orderDate);
    QVariant totalPrice_value = QVariant::fromValue(totalPrice);
    record.setValue(4, totalPrice_value);
    record.setValue(5, 0);
    purchaseModel->insertRecord(purchaseModel->rowCount(), record);
//    purchaseModel->submitAll();

    if (!purchaseModel->submitAll()) {
        qDebug() << "数据插入过程中发生错误：" << purchaseModel->lastError().text();
    }

    //插入order——items表
    int order_id = purchaseModel->query().lastInsertId().toInt();
    purchaseModel->setTable("order_items");
    record = purchaseModel->record();

    for(int i=0;i<med_nums;i++){
        qDebug() << order_id << " " << med_id[i] << " " << med_amount[i] << " " << med_price[i] << " " << med_amount[i]*med_price[i];

        record.setValue(1,order_id);
        record.setValue(2,med_id[i]);
        record.setValue(3, med_amount[i]);
        record.setValue(4, med_price[i]);
        record.setValue(5, med_amount[i]*med_price[i]);

        purchaseModel->insertRecord(purchaseModel->rowCount(), record);
    //    purchaseModel->submitAll();

        if (!purchaseModel->submitAll()) {
            qDebug() << "数据插入过程中发生错误：" << purchaseModel->lastError().text();
        }
    }

    QMessageBox::information(this, "提示", "添加成功!");
    purchaseDialog->close();

    //更新视图
    QString sql_all = QString("select `order`.order_id, user.user_name, supplier.supplier_name, `order`.order_date, `order`.total_price, `order`.status from `order` JOIN user on `order`.user_id = user.user_id join supplier on `order`.supplier_id = supplier.supplier_id;");
    purchaseModel_query->setQuery(sql_all);
    ui->tableView->setModel(purchaseModel_query);
}

void purchase::modifyOrder(){
    purchaseModifyDialog = new modifyPurchaseDialog(this);
    int curRow = ui->tableView->currentIndex().row();
//    purchaseModel->setTable("order");
//    purchaseModel->select();
    QSqlRecord record = purchaseModel_query->record(curRow);

    QString name = record.value(1).toString();
    purchaseModifyDialog->user->setCurrentText(name);
    QString supplier = record.value(2).toString();
    purchaseModifyDialog->supplier->setCurrentText(supplier);
    QString date = record.value(3).toString();
    purchaseModifyDialog->date->setText(date);
    QString price = record.value(4).toString();
    purchaseModifyDialog->total_price->setText(price);
    QString status = record.value(5).toString();
    if(status == "0"){
        purchaseModifyDialog->status->setText("未处理");
    }else if(status == "1"){
        purchaseModifyDialog->status->setText("拒绝");
    }else{
        purchaseModifyDialog->status->setText("通过");
    }
    purchaseModifyDialog->show();

    connect(purchaseModifyDialog->modifyButton,&QPushButton::clicked,this,&purchase::modifyOrderData);
}

void purchase::modifyOrderData(){
    int name = purchaseModifyDialog->user->currentIndex()+1;
    int supplier = purchaseModifyDialog->supplier->currentIndex();
    QString date = purchaseModifyDialog->date->text();
    QString price = purchaseModifyDialog->total_price->text();
    QString status = purchaseModifyDialog->status->text();

    int curRow = purchaseTableView->currentIndex().row();
    QSqlRecord record = purchaseModel->record(curRow);
    record.setValue(1,name);
    record.setValue(2,supplier);
    record.setValue(3,date);
    record.setValue(4,price);
    record.setValue(5,status);

    if(purchaseModel->setRecord(curRow, record))
    {
        purchaseModifyDialog->close();
        purchaseModel->submitAll();
        purchaseTableView->setEnabled(true);

        QMessageBox::information(this, "提示", "修改成功!");
    }
}

void purchase::deleteOrderData(){
    int curRow = purchaseTableView->currentIndex().row();
    purchaseModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("警告"),
                                      tr("你确定删除当前行吗？"),
                                      QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        purchaseModel->revertAll(); //如果不删除，则撤销
    else
        purchaseModel->submitAll(); //否则提交，在数据库中删除该行
}
