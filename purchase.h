#ifndef PURCHASE_H
#define PURCHASE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableView>
#include <QSqlQuery>
#include "index.h"
#include "addpurchasedialog.h"
#include "modifypurchasedialog.h"
#include "MyDelegatePurchase.cpp"
#include "purchasedetailsdialog.h"

namespace Ui {
class purchase;
}

class purchase : public QWidget
{
    Q_OBJECT

public:
    explicit purchase(QWidget *parent = nullptr);
    ~purchase();

private slots:
    void addOrder();
    void insertOrderData();
    void modifyOrder();
    void modifyOrderData();
    void deleteOrderData();
    void seeMore();

private:
    Ui::purchase *ui;
    QSqlTableModel *purchaseModel;
    QSqlQueryModel* purchaseModel_query;
    addPurchaseDialog *purchaseDialog;
    modifyPurchaseDialog* purchaseModifyDialog;
    QTableView* purchaseTableView;
    QSqlQuery query;
    MyDelegatePurchase* delegate;
    purchaseDetailsDialog* detailsDialog;
};

#endif // PURCHASE_H
