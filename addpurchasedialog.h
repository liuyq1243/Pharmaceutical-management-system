#ifndef ADDPURCHASEDIALOG_H
#define ADDPURCHASEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QScrollArea>

class addPurchaseDialog : public QDialog
{

private slots:
    void onCheckBoxStateChanged(int state);

public:
    addPurchaseDialog(QWidget *parent = nullptr);

    QComboBox *user;
    QComboBox *supplier;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHash<QCheckBox*, QLineEdit*> medicineQuantityMap;

    QPushButton *addButton;
};

#endif
