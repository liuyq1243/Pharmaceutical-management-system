#include <QStyledItemDelegate>
#include <QPainter>

class MyDelegate : public QStyledItemDelegate
{
public:
    explicit MyDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

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
        // 根据第三列的值来决定显示的文本
        if (index.column() == 2)
        {
            int userType = index.data().toInt();
            QString displayText = (userType == 0) ? "管理员" : (userType == 1) ? "供应商" : "采购员";
            QStyledItemDelegate::paint(painter, option, QModelIndex(index.siblingAtColumn(0))); // 保留其他列的显示
            painter->drawText(option.rect, Qt::AlignCenter, displayText);
        }
        else
        {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};
