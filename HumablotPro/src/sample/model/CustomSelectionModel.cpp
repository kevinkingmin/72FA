#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include <QMouseEvent>

class CustomSelectionModel : public QItemSelectionModel {
public:
    explicit CustomSelectionModel(QAbstractItemModel* model, QObject* parent = nullptr) :
        QItemSelectionModel(model, parent) {}

protected:
    void select(const QItemSelection& selection, QItemSelectionModel::SelectionFlags command) override {
        Q_UNUSED(command)
        QItemSelection newSelection;
        foreach (const QModelIndex& index, selection.indexes()) {
            if (!newSelection.contains(index) && index.column() == currentIndex().column()) {
                newSelection.select(index, index);
            }
        }
        QItemSelectionModel::select(newSelection, QItemSelectionModel::ClearAndSelect);
    }

    //void mousePressEvent(QMouseEvent* event) override {
    //    if (event->buttons() == Qt::LeftButton) {
    //        QModelIndex index = QItemSelectionModel::model()->indexAt(event->pos());
    //        if (index.isValid() && index.column() == currentIndex().column()) {
    //            QItemSelection newSelection(index, index);
    //            QItemSelectionModel::select(newSelection, QItemSelectionModel::ClearAndSelect);
    //            return;
    //        }
    //    }
    //    QItemSelectionModel::mousePressEvent(event);
    }
};