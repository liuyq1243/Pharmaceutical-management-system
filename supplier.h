#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableView>
#include "addsupplierdialog.h"
#include "modifysupplierdialog.h"
#include "index.h"

namespace Ui {
class supplier;
}

class index;

class supplier : public QWidget
{
    Q_OBJECT

public:
    explicit supplier(QWidget *parent = nullptr);
    ~supplier();

private slots:
    void addSupplier(); //添加新供应商
    void insertSupplierData();  //在数据表中添加新纪录
    void modifySupplier();  //修改供应商信息
    void modifySupplierData();  //修改数据表中数据
    void deleteSupplierData();

private:
    Ui::supplier *ui;
    QSqlTableModel *supplierModel;
    QSqlQueryModel* supplierModel_query;
    addSupplierDialog *supplierDialog;
    modifySupplierDialog* supplierModifyDialog;
    QTableView* supplierTableView;
};

#endif // SUPPLIER_H
