#ifndef MODIFYUSERDIALOG_H
#define MODIFYUSERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class modifyUserDialog : public QDialog
{

public:
    modifyUserDialog(QWidget *parent = nullptr);
    ~modifyUserDialog();

    QLineEdit *nameEdit;
    QComboBox *typeEdit;
    QLineEdit *pwdEdit;
    QPushButton *modifyButton;
};

#endif
