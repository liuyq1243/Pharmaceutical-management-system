#include "supplier.h"
#include "ui_supplier.h"

supplier::supplier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::supplier)
{
    ui->setupUi(this);

    supplierTableView = ui->tableView;

    supplierModel_query = new QSqlQueryModel();

    supplierModel = new QSqlTableModel();
    supplierModel->setTable("supplier");
    supplierModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    supplierModel->setHeaderData(0,Qt::Horizontal, "编号");
    supplierModel->setHeaderData(1,Qt::Horizontal, "供应商名称");
    supplierModel->setHeaderData(2,Qt::Horizontal, "联系人");
    supplierModel->setHeaderData(3,Qt::Horizontal, "联系方式");
    supplierModel->setHeaderData(4,Qt::Horizontal, "地址");
    supplierModel->setHeaderData(5,Qt::Horizontal, "添加日期");
    supplierModel->select(); //选取整个表的所有行

    ui->tableView->setModel(supplierModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    //添加新供应商
    connect(ui->btn_add, &QPushButton::clicked, this, &supplier::addSupplier);

    //search
    connect(ui->btn_search, &QPushButton::clicked, this, [&]{
        QString supplier_name = ui->supName_input->text();
        QString supplier_location = ui->locations->currentText();
        QString person_name = ui->personName_input->text();

        QString sql = QString("select * from supplier where supplier_name like '%%%1%%' and supplier_address like '%%%2%%' and supplier_contact like '%%%3%%';")
                .arg(supplier_name).arg(supplier_location).arg(person_name);
        qDebug() << sql;
        supplierModel_query->setQuery(sql);
        ui->tableView->setModel(supplierModel_query);

        supplierModel_query->setHeaderData(0,Qt::Horizontal, "编号");
        supplierModel_query->setHeaderData(1,Qt::Horizontal, "供应商名称");
        supplierModel_query->setHeaderData(2,Qt::Horizontal, "联系人");
        supplierModel_query->setHeaderData(3,Qt::Horizontal, "联系方式");
        supplierModel_query->setHeaderData(4,Qt::Horizontal, "地址");
        supplierModel_query->setHeaderData(5,Qt::Horizontal, "添加日期");
    });

    //返回
    connect(ui->btn_back, &QPushButton::clicked, this, [&]{
        this->close();
        index *page_index = new index();
        page_index->show();
    });

    //重置
    connect(ui->btn_reset, &QPushButton::clicked, this, [&]{
       ui->supName_input->clear();
       ui->personName_input->clear();
       ui->locations->setCurrentIndex(-1);

       supplierModel->select(); //选取整个表的所有行
       ui->tableView->setModel(supplierModel);
    });

    //修改
    connect(ui->btn_modify, &QPushButton::clicked, this, &supplier::modifySupplier);

    //删除
    connect(ui->btn_del, &QPushButton::clicked, this, &supplier::deleteSupplierData);
}

supplier::~supplier()
{
    delete ui;
}

void supplier::addSupplier(){
    supplierDialog = new addSupplierDialog();
    supplierDialog->show();
    connect(supplierDialog->addButton,&QPushButton::clicked,this,&supplier::insertSupplierData);
}

void supplier::insertSupplierData()
{
    QString supplierName = supplierDialog->nameEdit->text();
    QString supplierAddr = supplierDialog->addrEdit->currentText();
    QDate currentDate = QDateTime::currentDateTime().date();
    QString supplierDate = currentDate.toString("yyyy.MM.dd");
    QString supplierContact = supplierDialog->contactEdit->text();
    QString supplierTele = supplierDialog->teleEdit->text();

    QSqlRecord record = supplierModel->record();
    record.setValue(1,supplierName);
    record.setValue(2,supplierContact);
    record.setValue(3,supplierTele);
    record.setValue(4,supplierAddr);
    record.setValue(5,supplierDate);
    supplierModel->insertRecord(supplierModel->rowCount(), record);
    supplierModel->submitAll();

    QMessageBox::information(this, "提示", "添加成功!");
    supplierDialog->close();
}

void supplier::modifySupplier()
{
    supplierModifyDialog = new modifySupplierDialog(this);
    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = supplierModel->record(curRow);

    QString name = record.value(1).toString();
    supplierModifyDialog->nameEdit->setText(name);
    QString contact = record.value(2).toString();
    supplierModifyDialog->contactEdit->setText(contact);
    QString telephone = record.value(3).toString();
    supplierModifyDialog->teleEdit->setText(telephone);
    QString address = record.value(4).toString();
    supplierModifyDialog->addrEdit->setCurrentText(address);
    supplierModifyDialog->show();

    connect(supplierModifyDialog->modifyButton,&QPushButton::clicked,this,&supplier::modifySupplierData);
}

void supplier::modifySupplierData(){
    QString supplierName = supplierModifyDialog->nameEdit->text();
    QString supplierAddr = supplierModifyDialog->addrEdit->currentText();
    QString supplierContact = supplierModifyDialog->contactEdit->text();
    QString supplierTele = supplierModifyDialog->teleEdit->text();

    int curRow = supplierTableView->currentIndex().row();
    QSqlRecord record = supplierModel->record(curRow);
    record.setValue(1,supplierName);
    record.setValue(2,supplierContact);
    record.setValue(3,supplierTele);
    record.setValue(4,supplierAddr);

    if(supplierModel->setRecord(curRow, record))
    {
        supplierModifyDialog->close();
        supplierModel->submitAll();
        supplierTableView->setEnabled(true);

        QMessageBox::information(this, "提示", "修改成功!");
    }
}

void supplier::deleteSupplierData(){
    int curRow = supplierTableView->currentIndex().row();
    supplierModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("警告"),
                                      tr("你确定删除当前行吗？"),
                                      QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        supplierModel->revertAll(); //如果不删除，则撤销
    else
        supplierModel->submitAll(); //否则提交，在数据库中删除该行
}
