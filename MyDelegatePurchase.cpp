#include <QStyledItemDelegate>
#include <QPainter>

class MyDelegatePurchase : public QStyledItemDelegate
{
public:
    explicit MyDelegatePurchase(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        // 如果需要编辑，可以在这里创建编辑器
        return QStyledItemDelegate::createEditor(parent, option, index);
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        // 将模型中的数据设置到编辑器上
        QStyledItemDelegate::setEditorData(editor, index);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        // 将编辑器上的数据保存到模型中
        QStyledItemDelegate::setModelData(editor, model, index);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        // 根据第六列的值来决定显示的文本
        if (index.column() == 5)
        {
            int userType = index.data().toInt();
            QString displayText = (userType == 0) ? "未处理" : (userType == 1) ? "拒绝" : "通过";
            QStyledItemDelegate::paint(painter, option, QModelIndex(index.siblingAtColumn(0))); // 保留其他列的显示
            painter->drawText(option.rect, Qt::AlignCenter, displayText);
        }
        else
        {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};
