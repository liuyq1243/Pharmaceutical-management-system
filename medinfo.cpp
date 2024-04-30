#include "medinfo.h"
#include "ui_medinfo.h"

medInfo::medInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("药品管理");

    medModel_table = new QSqlTableModel();
    medModel_table->setTable("med");
    medModel_table->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    medModel_table->select(); //选取整个表的所有行
    qDebug() << "lines nums: " << medModel_table->rowCount();

    supplierMap["江苏苏中药业集团股份有限公司"] = 0;
    supplierMap["海南碧凯药业有限公司"] = 1;
    supplierMap["佛山冯了性药业有限公司"] = 2;
    supplierMap["深圳京果制药有限公司"] = 3;
    supplierMap["哈尔滨儿童制药厂有限公司"] = 4;

    medTableView = ui->tableView;

    //链接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("hospital");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "链接数据库成功");
    }
    else {
        QMessageBox::information(this, "infor", "数据库连接失败");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
//    QSqlQuery query(db);
//    query = new QSqlQuery(db);

    medModel = new QSqlQueryModel();
    QString sql_all = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id order by med_id;");
    medModel->setQuery(sql_all);
    ui->tableView->setModel(medModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    medModel->setHeaderData(0,Qt::Horizontal, "药品名称");
    medModel->setHeaderData(1,Qt::Horizontal, "药品类型");
    medModel->setHeaderData(2,Qt::Horizontal, "药品描述");
    medModel->setHeaderData(3,Qt::Horizontal, "供应商");
    medModel->setHeaderData(4,Qt::Horizontal, "价格");
    medModel->setHeaderData(5,Qt::Horizontal, "药品用途");


//    QList<QWidget*> meds = query_med(db, sql_all);
//    med_grid = getMedsGrid(meds);

//    ui->horizontalLayout_3->addLayout(med_grid);
    ui->btn_all->setDisabled(true);
    //all
    connect(ui->btn_all, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(true);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_all = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id order by med_id;");
        medModel->setQuery(sql_all);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med;");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-woman
    connect(ui->type_woman, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(true);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_1 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '妇科用药' order by med_id;");
        medModel->setQuery(sql_1);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '妇科用药';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-man
    connect(ui->type_man, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(true);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_2 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '男科用药' order by med_id;");
        medModel->setQuery(sql_2);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '男科用药';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-kid
    connect(ui->type_kid, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(true);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_3 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '儿科用药' order by med_id;");
        medModel->setQuery(sql_3);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '儿科用药';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-nerve
    connect(ui->type_nerve, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(true);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_1 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '神经系统用药' order by med_id;");
        medModel->setQuery(sql_1);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '神经系统用药';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-rumor
    connect(ui->type_tumour, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(true);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_1 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '抗肿瘤类药物' order by med_id;");
        medModel->setQuery(sql_1);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '抗肿瘤类药物';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-skin
    connect(ui->type_skin, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(true);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString sql_1 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '皮肤类用药' order by med_id;");
        medModel->setQuery(sql_1);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '皮肤类用药';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type_eye
    connect(ui->type_eye, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(true);
        ui->type_hot->setDisabled(false);

        QString sql_1 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '眼科用药' order by med_id;");
        medModel->setQuery(sql_1);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QString sql = QString("select med_pic,med_name,med_price from hospital.med where med_type = '眼科用药';");
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });
    //type-hot
    connect(ui->type_hot, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_eye->setDisabled(false);
        ui->type_hot->setDisabled(true);

        QString sql_1 = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med.med_type = '治解热镇痛药物' order by med_id;");
        medModel->setQuery(sql_1);
        ui->tableView->setModel(medModel);
    });

    //根据商品名称或供应商名称进行搜索
    connect(ui->btn_search, &QPushButton::clicked, this, [&]{
        ui->btn_all->setDisabled(false);
        ui->type_woman->setDisabled(false);
        ui->type_man->setDisabled(false);
        ui->type_kid->setDisabled(false);
        ui->type_nerve->setDisabled(false);
        ui->type_tumour->setDisabled(false);
        ui->type_skin->setDisabled(false);
        ui->type_hot->setDisabled(false);

        QString med_name = ui->med_name_input->text();
        QString supplier_name = ui->supplier_name_input->text();

        QString sql = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from hospital.med JOIN supplier ON med.supplier_id = supplier.supplier_id where med.med_name like '%%%1%%' and supplier_name like '%%%2%%' order by med_id;")
                .arg(med_name).arg(supplier_name);

        medModel->setQuery(sql);
        ui->tableView->setModel(medModel);

//        //删除
//        deleteLayout(med_grid, ui->horizontalLayout_3);
//        //更换新的
//        QList<QWidget*> med_list = query_med(db, sql);
//        med_grid = getMedsGrid(med_list);
//        ui->horizontalLayout_3->addLayout(med_grid);
    });

    //返回
    connect(ui->pushButton, &QPushButton::clicked, this, [&]{    
        // 等待事件循环处理完毕
        QCoreApplication::processEvents();
        this->close();
        index* page_index = new index();
        page_index->show();
    });

    //增加
    connect(ui->btn_add, &QPushButton::clicked, this, &medInfo::addMed);

    //修改
    connect(ui->btn_modify, &QPushButton::clicked, this, &medInfo::modifyMed);

    //重置
    connect(ui->btn_reset, &QPushButton::clicked, this, [&]{
        ui->med_name_input->clear();
        ui->supplier_name_input->clear();

        QString sql_all = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id;");
        medModel->setQuery(sql_all);
        ui->tableView->setModel(medModel);
    });

    //删除
    connect(ui->btn_del, &QPushButton::clicked, this, &medInfo::deleteSupplierData);
}

medInfo::~medInfo()
{
    delete ui;
}

QList<QWidget*> medInfo::query_med(QSqlDatabase db, QString sql){
    QSqlQuery query(db);
    query.exec(sql);
    QList<QWidget*> meds;

    while (true == query.next()) {  //一行一行遍历
        QString pic_url = query.value("med_pic").toString();
        QString med_name = query.value("med_name").toString();
        double med_price = query.value("med_price").toDouble();

//         qDebug() << pic_url;
//         qDebug() << med_name;
//         qDebug() << med_price;

        QWidget* med = new med_sim(pic_url, med_price, med_name);
        meds.append(med);
    }

    return meds;
}

QGridLayout* medInfo::getMedsGrid(QList<QWidget*> meds){
    QGridLayout* med_grid = new QGridLayout();
    //一行四个
    int i = 0, j=0;//行数
    for(int k=0;k<meds.size();k++){
        med_grid->addWidget(meds.at(k), i, j++);
        if(j>=4)   i++,j=0;
    }

    return med_grid;
}

void medInfo::deleteLayout(QGridLayout* layout, QHBoxLayout* hlayout){
    // 从水平布局中移除网格布局
    hlayout->removeItem(layout);
    // 删除网格布局及其所有元素
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete layout;
}

void medInfo::addMed(){
    medDialog = new addMedDialog();
    medDialog->show();
    connect(medDialog->addButton,&QPushButton::clicked,this,&medInfo::insertMedData);
}

void medInfo::insertMedData()
{
    QString medName = medDialog->nameEdit->text();
    QString medType = medDialog->typeEdit->currentText();
    QString medPic = medDialog->medPicEdit->text();
    QString medSpec = medDialog->medSpecEdit->text();
    QString medSupplier = medDialog->supplierEdit->currentText();
    double medPrice = medDialog->medPriceEdit->text().toDouble();
    QString medInfo = medDialog->medInfoEdit->text();

    qDebug() << QString("%1 %2 %3 %4 %5 %6 %7").arg(medName).arg(medType).arg(medPic)
                .arg(medSpec).arg(supplierMap[medSupplier]).arg(medPrice).arg(medInfo);

    QSqlRecord record = medModel_table->record();
    record.setValue(1,medName);
    record.setValue(2,medType);
    record.setValue(3,medPic);
    record.setValue(4,medSpec);
    // 使用map 将medSupplier映射到数据表中
    QVariant supplierValue = QVariant::fromValue(supplierMap[medSupplier]);
    record.setValue(5,supplierValue);
    QVariant priceValue = QVariant::fromValue(medPrice);
    record.setValue(6,priceValue);
    record.setValue(7,medInfo);
    record.setValue(8,0);

    medModel_table->insertRecord(medModel_table->rowCount(), record);
    medModel_table->submitAll();
    if (!medModel_table->submitAll()) {
        qDebug() << "Error during data insertion: " << medModel_table->lastError().text();
    }

    QMessageBox::information(this, "提示", "添加成功!");

    //刷新页面
    QString sql_all = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id order by med_id;");
    medModel->setQuery(sql_all);
    medTableView->setModel(medModel);

    medDialog->close();
}

void medInfo::modifyMed()
{
    medModifyDialog = new modifyMedDialog(this);
    int curRow = ui->tableView->currentIndex().row();
    qDebug() << curRow;
//    QString sql = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id where med_id = %1 order by med_id;")
//            .arg(curRow);
    medModel_table->select();
    QSqlRecord record = medModel_table->record(curRow);

    int fieldCount = record.count();
    qDebug() << "Field count: " << fieldCount;

    for (int i = 0; i < fieldCount; ++i) {
        qDebug() << "Field " << i << ": " << record.fieldName(i) << " - " << record.value(i);
    }
//    qDebug() << medModel_table->rowCount();

    QString name = record.value(1).toString();
    medModifyDialog->nameEdit->setText(name);
    QString type = record.value(2).toString();
    medModifyDialog->typeEdit->setCurrentText(type);
    QString pic = record.value(3).toString();
    medModifyDialog->medPicEdit->setText(pic);
    QString spec = record.value(4).toString();
    medModifyDialog->medSpecEdit->setText(spec);
    int supplierNo = record.value(5).toInt();
    medModifyDialog->supplierEdit->setCurrentIndex(supplierNo);
    double price = record.value(6).toDouble();
    medModifyDialog->medPriceEdit->setText(QString::number(price));
    QString info = record.value(7).toString();
    medModifyDialog->medInfoEdit->setText(info);

    medModifyDialog->show();

    qDebug() << name;

    connect(medModifyDialog->modifyButton,&QPushButton::clicked,this,&medInfo::modifyMedData);
}

void medInfo::modifyMedData(){
    QString medName = medModifyDialog->nameEdit->text();
    QString medType = medModifyDialog->typeEdit->currentText();
    QString medPic = medModifyDialog->medPicEdit->text();
    QString medSpec = medModifyDialog->medSpecEdit->text();
    int medSupplier = medModifyDialog->supplierEdit->currentIndex();
    double medPrice = medModifyDialog->medPriceEdit->text().toDouble();
    QString medInfo = medModifyDialog->medInfoEdit->text();

    int curRow = medTableView->currentIndex().row();
    QSqlRecord record = medModel_table->record(curRow);
    record.setValue(1,medName);
    record.setValue(2,medType);
    record.setValue(3,medPic);
    record.setValue(4,medSpec);
    QVariant supplierValue = QVariant::fromValue(medSupplier);
    record.setValue(5,supplierValue);
    QVariant priceValue = QVariant::fromValue(medPrice);
    record.setValue(6,priceValue);
    record.setValue(7,medInfo);

    if(medModel_table->setRecord(curRow, record))
    {
        medModifyDialog->close();
        medModel_table->submitAll();
        medTableView->setEnabled(true);

        QMessageBox::information(this, "提示", "修改成功!");
        //刷新页面
        QString sql_all = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id order by med_id;");
        medModel->setQuery(sql_all);
        medTableView->setModel(medModel);
    }
}

void medInfo::deleteSupplierData(){
    int curRow = medTableView->currentIndex().row();
    medModel_table->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("警告"),
                                      tr("你确定删除当前行吗？"),
                                      QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        medModel_table->revertAll(); //如果不删除，则撤销
    else{
        medModel_table->submitAll(); //否则提交，在数据库中删除该行

        //刷新页面
        QString sql_all = QString("select med.med_name,med.med_type,med.med_spec,supplier.supplier_name,med.med_price,med.med_info from med JOIN supplier on med.supplier_id = supplier.supplier_id order by med_id;");
        medModel->setQuery(sql_all);
        medTableView->setModel(medModel);
    }


}
