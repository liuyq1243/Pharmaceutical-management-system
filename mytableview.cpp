#include <QTableView>
#include <QMouseEvent>
#include <QDebug>

class MyTableView : public QTableView {
public:
    MyTableView(QWidget *parent = nullptr) : QTableView(parent) {}

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            QModelIndex index = indexAt(event->pos());
            if (index.isValid()) {
                // 处理双击事件，你可以在这里执行你的操作
                qDebug() << "Double-clicked on row:" << index.row() << "column:" << index.column();
            }
        }

        QTableView::mouseDoubleClickEvent(event);
    }
};
