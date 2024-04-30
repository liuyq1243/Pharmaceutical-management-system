#ifndef PURCHASEDETAILSDIALOG_H
#define PURCHASEDETAILSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class purchaseDetailsDialog : public QDialog
{

public:
    purchaseDetailsDialog(QWidget *parent = nullptr);
    ~purchaseDetailsDialog();

    QLabel *orderID;
    QLabel *user;
    QLabel *supplier;
    QLabel *date;
    QLabel *price;
    QLabel *status;
    QScrollArea *scrollArea;
    QPushButton *btn_pass;
    QPushButton *btn_reject;
};

#endif // PURCHASEDETAILSDIALOG_H
