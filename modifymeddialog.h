#ifndef MODIFYMEDDIALOG_H
#define MODIFYMEDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class modifyMedDialog : public QDialog
{
    Q_OBJECT

public:
    modifyMedDialog(QWidget *parent = nullptr);
    ~modifyMedDialog();

    QLineEdit *nameEdit;
    QComboBox *typeEdit;
    QLineEdit *medPicEdit;
    QLineEdit *medSpecEdit;
    QComboBox *supplierEdit;
    QLineEdit *medPriceEdit;
    QLineEdit *medInfoEdit;
    QPushButton *modifyButton;
};

#endif // MODIFYSUPPLIERDIALOG_H
