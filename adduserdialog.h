#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include "QLineEditPassword.h"

class addUserDialog : public QDialog
{
    Q_OBJECT

public:
    addUserDialog(QWidget *parent = nullptr);

    QLineEdit *nameEdit;
    QComboBox *typeEdit;
    QLineEdit *pwdEdit;
    QPushButton *addButton;
};

#endif
