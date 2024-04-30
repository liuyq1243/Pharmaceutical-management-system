#ifndef INDEX_H
#define INDEX_H

#include <QWidget>
#include <QStackedWidget>
#include <QTimer>
#include <QFile>
#include <QImageReader>
#include "medinfo.h"
#include "qanimationstackedwidget.h"
#include "supplier.h"
#include "user.h"
#include "purchase.h"

namespace Ui {
class index;
}

class medInfo;
class supplier;

class index : public QWidget
{
    Q_OBJECT

public:
    explicit index(QWidget *parent = nullptr);
    ~index();

private slots:
    void User();
    void Med();
    void Supplier();
    void Purchase();

private:
    Ui::index *ui;
    QTimer *timer;    //定时器
};

#endif // INDEX_H
