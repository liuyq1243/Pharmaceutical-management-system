#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableView>
#include "index.h"
#include "adduserdialog.h"
#include "modifyuserdialog.h"
#include "MyDelegate.cpp"

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();

private slots:
    void addUser();
    void insertUserData();
    void modifyUser();
    void modifyUserData();
    void deleteUserData();

private:
    Ui::user *ui;
    QSqlTableModel *userModel;
    QSqlQueryModel* userModel_query;
    addUserDialog *userDialog;
    modifyUserDialog* userModifyDialog;
    QTableView* userTableView;
    MyDelegate *delegate;
};

#endif // USER_H
