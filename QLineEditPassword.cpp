#include "QLineEditPassword.h"
#include <QFile>
#include <QHBoxLayout>
#include <QPushButton>

// 加载文件内容
inline bool LoadStyleFile(QString strFilePath, QString& strContent)
{
    QFile qssFile(strFilePath);
    qssFile.open(QFile::ReadOnly);
    if(!qssFile.isOpen())
    {
        return false;
    }

    strContent = qssFile.readAll();
    qssFile.close();

    return true;
}


QLineEditPassword::QLineEditPassword(QWidget *parent) : QLineEdit(parent)
{
    setEchoMode(QLineEdit::Password);

    QPushButton* button = new QPushButton();
    button->setCursor(Qt::PointingHandCursor);
    button->setCheckable(true);
    connect(button, &QPushButton::toggled, [this](bool checked) {
            if (checked)
            {
                setEchoMode(QLineEdit::Normal);
            }
            else
            {
                setEchoMode(QLineEdit::Password);
            }
        });

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addStretch();
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QString strStyle;
    if (LoadStyleFile(":/qss/QLineEditPasswordStyle.qss", strStyle))
    {
        setStyleSheet(strStyle);
    }
}
