#include "med_sim.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QImageReader>
#include <QFile>

med_sim::med_sim(QWidget *parent)
    : QWidget{parent}
{

}

med_sim::med_sim(QString med_url, double med_price, QString med_name)
{
    // 步骤1：创建 QVBoxLayout
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    // 步骤2：添加 3 个 QLabel 到 QVBoxLayout
    QLabel *pic = new QLabel("Label 1");
    QLabel *price = new QLabel("Label 2");
    QLabel *name = new QLabel("Label 3");

    QImageReader reader(med_url);
    reader.setDevice(new QFile(med_url));
    QImage image = reader.read();
//    QImage* image = new QImage();
//    image->load(med_url);

    if(image.isNull()){
        qDebug() << "error"+med_url;
    }

    QImage resizedPixmap = image.scaled(QSize(230, 180),Qt::KeepAspectRatio);

//    QPixmap med_pic(med_url);
//    QPixmap resizedPixmap = med_pic.scaled(QSize(800, 600), Qt::KeepAspectRatio);
    pic->setFixedSize(230, 180);
    pic->setPixmap(QPixmap::fromImage(resizedPixmap));
    price->setText(QString::number(med_price)+" RMB");
    name->setText(med_name);

    verticalLayout->addWidget(pic);
    verticalLayout->addWidget(price);
    verticalLayout->addWidget(name);

    // 设置布局
    setLayout(verticalLayout);
}
