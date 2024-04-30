#ifndef MEDINFO_H
#define MEDINFO_H

#include <QWidget>
#include <QSqlDatabase>
#include <QPluginLoader>
#include <QSql>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTableView>
#include <unordered_map>
#include "med_sim.h"
#include "index.h"
#include "addmeddialog.h"
#include "modifymeddialog.h"

namespace Ui {
class medInfo;
}

class medInfo : public QWidget
{
    Q_OBJECT

public:
    explicit medInfo(QWidget *parent = nullptr);
    ~medInfo();

private slots:
    void addMed();
    void insertMedData();
    void modifyMed();
    void modifyMedData();
    void deleteSupplierData();

private:
    QGridLayout* getMedsGrid(QList<QWidget*> meds);
    QList<QWidget*> query_med(QSqlDatabase db, QString sql);
    void deleteLayout(QGridLayout* layout, QHBoxLayout* hlayout);

private:
    Ui::medInfo *ui;
    QSqlDatabase db;
//    QGridLayout* med_grid;
    QSqlQueryModel* medModel;
    QSqlTableModel* medModel_table;
    addMedDialog* medDialog;
    modifyMedDialog* medModifyDialog;
    QTableView* medTableView;

    std::unordered_map<QString, int> supplierMap;
};

#endif // MEDINFO_H
