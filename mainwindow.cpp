#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");

//    qDebug()<<"available drivers:";
//        QStringList drivers = QSqlDatabase::drivers();
//        foreach(QString driver, drivers)
//            qDebug()<<driver;
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

    //输入处理
//    ui->pwd_input->setEchoMode(QLineEdit::Password);    //密码输入不可见
    QRegularExpression  rx("[a-zA-Z0-9!@#%^&*()_]+$"); //创建一个正则表达式对象rx
    QRegularExpressionValidator *pReg = new QRegularExpressionValidator(rx, this); //创建一个过滤器对象
    ui->username_input->setValidator(pReg); //限制用户名范围
    ui->pwd_input->setValidator(pReg); //限制密码范围

    //登录
    connect(ui->btn_login,SIGNAL(clicked(bool)),this,SLOT(login()));

    //返回主页
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::login()
{
    //验证登录
    QString user,pwd;
    user = ui->username_input->text();
    pwd = ui->pwd_input->text();
    //pwd Base64编码
    QByteArray byteA;
    byteA=pwd.toUtf8();
    byteA=byteA.toBase64();
    char * cbyteA=byteA.data();
    pwd = QString(cbyteA);
    qDebug() << pwd;

    QSqlQuery query(db);
    //sql预处理 防止sql注入
//    query.prepare("select user_pwd from hospital.user where user_name = ?");
//    query.addBindValue(user);
//    query.execBatch();

    QString sql = QString("select user_pwd from hospital.user where user_name = '%1'")
                .arg(user);
    query.exec(sql);
    query.next();
    QString sel_pwd = query.value(0).toString();
    qDebug() << sel_pwd;

//    if(pwd == sel_pwd){
    if(pwd == sel_pwd){
        QMessageBox::information(this, "提示", "登陆成功");
        // 设置全局属性
        QCoreApplication::instance()->setProperty("user", QVariant(user));
        this->close();
        page_index = new index();
        page_index->show();
    }else{
        QMessageBox::information(this, "提示", "账户名或密码错误");
    }
}
