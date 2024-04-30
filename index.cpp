#include "index.h"
#include "ui_index.h"

index::index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::index)
{
    ui->setupUi(this);
    this->setWindowTitle("首页");
    ui->nameLabel->setText(QCoreApplication::instance()->property("user").toString());

    //主页上循环转换栏动画
    QLabel *pic1 = new QLabel("pic1");
    QLabel *pic2 = new QLabel("pic2");
    QLabel *pic3 = new QLabel("pic3");

    QImageReader reader(":/pictures/med_pic/0.jpeg");
    reader.setDevice(new QFile(":/pictures/med_pic/0.jpeg"));
    QImage image = reader.read();

    if(image.isNull()){
        qDebug() << "error 0.jpeg";
    }

    QImage resizedPixmap = image.scaled(QSize(230, 180),Qt::KeepAspectRatio);
    pic1->setFixedSize(230, 180);
    pic1->setPixmap(QPixmap::fromImage(resizedPixmap));

    QImageReader reader2(":/pictures/med_pic/1.jpeg");
    reader.setDevice(new QFile(":/pictures/med_pic/1.jpeg"));
    image = reader.read();

    if(image.isNull()){
        qDebug() << "error 1.jpeg";
    }

    resizedPixmap = image.scaled(QSize(230, 180),Qt::KeepAspectRatio);
    pic2->setFixedSize(230, 180);
    pic2->setPixmap(QPixmap::fromImage(resizedPixmap));

    QImageReader reader3(":/pictures/med_pic/2.jpeg");
    reader.setDevice(new QFile(":/pictures/med_pic/2.jpeg"));
    image = reader.read();

    if(image.isNull()){
        qDebug() << "error 2.jpeg";
    }

    resizedPixmap = image.scaled(QSize(230, 180),Qt::KeepAspectRatio);
    pic3->setFixedSize(230, 180);
    pic3->setPixmap(QPixmap::fromImage(resizedPixmap));

    //图片居中显示
    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget;
    QWidget *page3 = new QWidget;
    QVBoxLayout *cen_p1 = new QVBoxLayout(page1);
    cen_p1->addWidget(pic1);
    cen_p1->setAlignment(Qt::AlignCenter);
    QVBoxLayout *cen_p2 = new QVBoxLayout(page2);
    cen_p2->addWidget(pic2);
    cen_p2->setAlignment(Qt::AlignCenter);
    QVBoxLayout *cen_p3 = new QVBoxLayout(page3);
    cen_p3->addWidget(pic3);
    cen_p3->setAlignment(Qt::AlignCenter);


    ui->stackedWidget->addWidget(page1);
    ui->stackedWidget->addWidget(page2);
    ui->stackedWidget->addWidget(page3);
    ui->stackedWidget->setAnimationDuration(3000);
    ui->stackedWidget->setAnimationMode(Quit2L);
//    ui->stackedWidget->StartStackedWidgetAnimation(0,1);
//    QAnimationStackedWidget* animationStackedWidget = new QAnimationStackedWidget(this);
//    animationStackedWidget->addWidget(pic1);
//    animationStackedWidget->addWidget(pic2);
//    animationStackedWidget->addWidget(pic3);
//    animationStackedWidget->setAnimationDuration(2000);
//    animationStackedWidget->setAnimationMode(L2R);

    timer = new QTimer(this);
    timer->setInterval(5000);
    int i = 0;  //轮转
    connect(timer,&QTimer::timeout,this,[&]{
        ui->stackedWidget->StartStackedWidgetAnimation(i%3,(i+1)%3);
        i++;
    });
    timer->start();

    //跳转其他页面
//    connect(ui->btn_index,SIGNAL(clicked(bool)),this,SLOT(Index()));
    connect(ui->btn_med,SIGNAL(clicked(bool)),this,SLOT(Med()));
    connect(ui->btn_supplier,SIGNAL(clicked(bool)),this,SLOT(Supplier()));
    connect(ui->btn_person,SIGNAL(clicked(bool)),this,SLOT(User()));
    connect(ui->btn_purchase, &QPushButton::clicked, this, &index::Purchase);
    connect(ui->btn_exit, &QPushButton::clicked, this, &QCoreApplication::quit);
}

index::~index()
{
    delete ui;
}

void index::User()
{
    this->close();
    user *user_page = new user();
    user_page->show();
}

void index::Med()
{
    //切换至药品信息页面
    this->close();
    medInfo *medinfo = new medInfo();
    medinfo->show();
}

void index::Supplier()
{
    this->close();
    supplier *supplier_page = new supplier();
    supplier_page->show();
}

void index::Purchase(){
    this->close();
    purchase *purchase_page = new purchase();
    purchase_page->show();
}
