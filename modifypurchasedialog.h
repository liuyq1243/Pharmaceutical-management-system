#ifndef MODIFYPURCHASEDIALOG_H
#define MODIFYPURCHASEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQueryModel>

class modifyPurchaseDialog : public QDialog
{
    Q_OBJECT

public:
    modifyPurchaseDialog(QWidget *parent = nullptr);
    ~modifyPurchaseDialog();


    QComboBox* user;
    QComboBox* supplier;
    QLabel* date;
    QLabel* total_price;
    QLabel* status;
    QPushButton *modifyButton;
};

#endif // MODIFYSUPPLIERDIALOG_H
