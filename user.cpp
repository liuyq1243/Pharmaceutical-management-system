#include "user.h"
#include "ui_user.h"

user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);

    userModel_query = new QSqlQueryModel();

    userTableView = ui->tableView;
    userModel = new QSqlTableModel();

    userModel->setTable("user");
    userModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    userModel->setHeaderData(0,Qt::Horizontal, "用户编号");
    userModel->setHeaderData(1,Qt::Horizontal, "用户账号");
    userModel->setHeaderData(2,Qt::Horizontal, "用户类型");
    userModel->setHeaderData(3,Qt::Horizontal, "用户密码");

    //不能删除 要不然insert不进去数据库
//    userModel->removeColumn(3);

    userModel->select(); //选取整个表的所有行

    //第三列显示
    // 创建委托
    delegate = new MyDelegate(this);
    // 将委托应用到QTableView上，第三列为 userType 列
    ui->tableView->setItemDelegateForColumn(2, delegate);

    ui->tableView->setModel(userModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑

    //增
    connect(ui->btn_add, &QPushButton::clicked, this, &user::addUser);

    //修改
    connect(ui->btn_modify, &QPushButton::clicked, this, &user::modifyUser);

    //删除
    connect(ui->btn_del, &QPushButton::clicked, this, &user::deleteUserData);

    //重置
    connect(ui->btn_reset, &QPushButton::clicked, this, [&]{
        ui->nameInput->clear();
        ui->comboBox->setCurrentIndex(-1);

        userModel->select(); //选取整个表的所有行
        ui->tableView->setModel(userModel);


    });

    //返回
    connect(ui->btn_back, &QPushButton::clicked, this, [&]{
        this->close();
        index *index_page = new index();
        index_page->show();
    });

    //搜索
    connect(ui->btn_search, &QPushButton::clicked, this, [&]{
        QString user_name = ui->nameInput->text();
        int user_type = ui->comboBox->currentIndex();

        QString sql;    //根据是否选中用户类型进行查询
        switch (user_type) {
            case 0: sql = QString("select * from user where user_name like '%%%1%%'").arg(user_name);break;
            case 1: sql = QString("select * from user where user_name like '%%%1%%' and user_level = 0").arg(user_name);break;
            case 2: sql = QString("select * from user where user_name like '%%%1%%' and user_level = 1").arg(user_name);break;
            case 3: sql = QString("select * from user where user_name like '%%%1%%' and user_level = 2").arg(user_name);break;
        }

        qDebug() << sql;
        userModel_query->setQuery(sql);
        ui->tableView->setModel(userModel_query);

        userModel_query->setHeaderData(0,Qt::Horizontal, "用户编号");
        userModel_query->setHeaderData(1,Qt::Horizontal, "用户账号");
        userModel_query->setHeaderData(2,Qt::Horizontal, "用户类型");
        userModel_query->setHeaderData(3,Qt::Horizontal, "用户密码");
    });
}

user::~user()
{
    delete ui;
}

void user::addUser(){
    userDialog = new addUserDialog();
    userDialog->show();
    connect(userDialog->addButton,&QPushButton::clicked,this,&user::insertUserData);
}

void user::insertUserData(){
    QString userName = userDialog->nameEdit->text();
    int userType = userDialog->typeEdit->currentIndex();
    QString userPwd = userDialog->pwdEdit->text();
    qDebug() << userPwd;

    //base64编码
    QByteArray byteA;
    byteA=userPwd.toUtf8();
    byteA=byteA.toBase64();
    char * cbyteA=byteA.data();
    userPwd = QString(cbyteA);

    qDebug() << userPwd;

    QSqlRecord record = userModel->record();
    record.setValue(1,userName);
    record.setValue(2,userType);
    record.setValue(3,userPwd);
    userModel->insertRecord(userModel->rowCount(), record);
    userModel->submitAll();

    if (!userModel->submitAll()) {
        qDebug() << "数据插入过程中发生错误：" << userModel->lastError().text();
    }


    QMessageBox::information(this, "提示", "添加成功!");
    userDialog->close();


}

void user::modifyUser(){
    userModifyDialog = new modifyUserDialog(this);
    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = userModel->record(curRow);

    QString name = record.value(1).toString();
    userModifyDialog->nameEdit->setText(name);
    int type = record.value(2).toInt();
    userModifyDialog->typeEdit->setCurrentIndex(type);
    QString pwd = record.value(3).toString();
    //pwd base64解码
    QByteArray byteA;
    byteA=pwd.toUtf8();
    byteA = QByteArray::fromBase64(byteA);
    char * cbyteA=byteA.data();
    pwd = QString(cbyteA);

    userModifyDialog->pwdEdit->setText(pwd);
    userModifyDialog->show();

    connect(userModifyDialog->modifyButton,&QPushButton::clicked,this,&user::modifyUserData);
}

void user::modifyUserData(){
    QString userName = userModifyDialog->nameEdit->text();
    int userType = userModifyDialog->typeEdit->currentIndex();
    QString userPwd = userModifyDialog->pwdEdit->text();

    int curRow = userTableView->currentIndex().row();
    QSqlRecord record = userModel->record(curRow);
    record.setValue(1,userName);
    record.setValue(2,userType);
    //base64编码
    QByteArray byteA;
    byteA=userPwd.toUtf8();
    byteA=byteA.toBase64();
    char * cbyteA=byteA.data();
    userPwd = QString(cbyteA);

    record.setValue(3,userPwd);

    if(userModel->setRecord(curRow, record))
    {
        userModifyDialog->close();
        userModel->submitAll();
        userTableView->setEnabled(true);

        QMessageBox::information(this, "提示", "修改成功!");
    }
}

void user::deleteUserData(){
    int curRow = userTableView->currentIndex().row();
    userModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("警告"),
                                      tr("你确定删除当前行吗？"),
                                      QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        userModel->revertAll(); //如果不删除，则撤销
    else
        userModel->submitAll(); //否则提交，在数据库中删除该行
}
