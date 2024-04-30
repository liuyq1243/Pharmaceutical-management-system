#ifndef MED_SIM_H
#define MED_SIM_H

#include <QWidget>

class med_sim : public QWidget
{
    Q_OBJECT
public:
    explicit med_sim(QWidget *parent = nullptr);
    explicit med_sim(QString med_url, double med_price, QString med_name);
signals:

};

#endif // MED_SIM_H
