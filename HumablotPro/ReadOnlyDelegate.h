#pragma once
#include <qitemdelegate.h>

// ����tableviewĳ��/�в��ɱ༭,
class ReadOnlyDelegate : public QItemDelegate
{

public:
	ReadOnlyDelegate(QWidget *parent = NULL) :QItemDelegate(parent)
	{}

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};



//class ReadOnlyDelegate :
//	public QItemDelegate
//{
//};

