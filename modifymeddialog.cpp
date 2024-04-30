#include "modifymeddialog.h"
#include <QGridLayout>

modifyMedDialog::modifyMedDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel("药品名称");
    nameEdit = new QLineEdit;
    QLabel *typeLabel = new QLabel("药品类型");
    typeEdit = new QComboBox;
    QStringList typeList;
    typeList<<"妇科用药"<<"男科用药"<<"儿科用药"<<"神经系统用药"<<"抗肿瘤类药物"<<"皮肤类用药"<<"眼科用药"<<"治解热镇痛药物";
    typeEdit->addItems(typeList);
    QLabel *picLabel = new QLabel("图片");
    medPicEdit = new QLineEdit;
    QLabel *supplierLabel = new QLabel("供应商");
    supplierEdit = new QComboBox;
    QStringList supplierList;
    supplierList<<"江苏苏中药业集团股份有限公司"<<"海南碧凯药业有限公司"<<"佛山冯了性药业有限公司"<<"深圳京果制药有限公司"<<"哈尔滨儿童制药厂有限公司";
    supplierEdit->addItems(supplierList);
    QLabel *specLabel = new QLabel("药品规格");
    medSpecEdit = new QLineEdit;
    QLabel *priceLabel = new QLabel("价格");
    medPriceEdit = new QLineEdit;
    QLabel *infoLabel = new QLabel("药品描述");
    medInfoEdit = new QLineEdit;
    modifyButton = new QPushButton("修改");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameEdit,0,1);
    layout->addWidget(typeLabel,1,0);
    layout->addWidget(typeEdit,1,1);
    layout->addWidget(picLabel,2,0);
    layout->addWidget(medPicEdit,2,1);
    layout->addWidget(supplierLabel,3,0);
    layout->addWidget(supplierEdit,3,1);
    layout->addWidget(specLabel,4,0);
    layout->addWidget(medSpecEdit,4,1);
    layout->addWidget(priceLabel,5,0);
    layout->addWidget(medPriceEdit,5,1);
    layout->addWidget(infoLabel,6,0);
    layout->addWidget(medInfoEdit,6,1);
    layout->addWidget(modifyButton,7,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}
modifyMedDialog::~modifyMedDialog()
{
}
