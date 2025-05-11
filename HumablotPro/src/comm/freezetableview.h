
#ifndef FREEZETABLEVIEW_H
#define FREEZETABLEVIEW_H

#include <QTableView>
class CustomerTableView;

class FreezeTableView : public QTableView {
     Q_OBJECT

public:
      explicit FreezeTableView(QAbstractItemModel * model);
      ~FreezeTableView() override;

    QTableView *getFrozenTableView() const;
protected:
    void resizeEvent(QResizeEvent *event) override;
      QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) override;

private:
      CustomerTableView *frozenTableView;
      void init();
      void updateFrozenTableGeometry();
      //liuxing20191016,当鼠标点击表格空白处时也需要发出信号。
      void mousePressEvent(QMouseEvent * event) override;
signals:
      //liuxing20191016
      void signalBlankArea(QMouseEvent *event);
      void signalDataArea(QMouseEvent *event);

private slots:
      void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
      void updateSectionHeight(int logicalIndex, int oldSize, int newSize);
};

#endif // FREEZETABLEVIEW_H
