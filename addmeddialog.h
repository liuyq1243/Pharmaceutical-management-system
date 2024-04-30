#ifndef ADDMEDDIALOG_H
#define ADDMEDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

class addMedDialog : public QDialog
{
    Q_OBJECT

public:
    addMedDialog(QWidget *parent = nullptr);

    QLineEdit *nameEdit;
    QComboBox *typeEdit;
    QLineEdit *medPicEdit;
    QLineEdit *medSpecEdit;
    QComboBox *supplierEdit;
    QLineEdit *medPriceEdit;
    QLineEdit *medInfoEdit;
    QPushButton *addButton;
};

#endif
