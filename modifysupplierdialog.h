#ifndef MODIFYSUPPLIERDIALOG_H
#define MODIFYSUPPLIERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class modifySupplierDialog : public QDialog
{
    Q_OBJECT

public:
    modifySupplierDialog(QWidget *parent = nullptr);
    ~modifySupplierDialog();

    QLineEdit *nameEdit;
    QComboBox *addrEdit;
    QComboBox *categoryEdit;
    QLineEdit *contactEdit;
    QLineEdit *teleEdit;
    QPushButton *modifyButton;
};

#endif // MODIFYSUPPLIERDIALOG_H
