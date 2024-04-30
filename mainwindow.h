#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "index.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QSqlDatabase>
#include <QPluginLoader>
#include <QSql>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "QLineEditPassword.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void login();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    index* page_index;
};
#endif // MAINWINDOW_H
