#ifndef COMBOXDELEGATE_H
#define COMBOXDELEGATE_H

#include <QItemDelegate>

class ComboxDelegate : public QItemDelegate
{
    Q_OBJECT

    struct ComBoxData
    {
        ComBoxData() {}
    };

public:
    ComboxDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor,const QModelIndex &index) const;
    void setModelData(QWidget *editor,QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &,
                              const QModelIndex &index) const;
};

#endif // COMBOXDELEGATE_H
