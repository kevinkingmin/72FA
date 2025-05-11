#include "ComboxDelegate.h"
#include <QComboBox>
#include <QListView>
#include "src/comm/GlobalData.h"
#include <QDebug>

ComboxDelegate::ComboxDelegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget *ComboxDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *editor = new QComboBox(parent);
	if (index.column() == 4)
	{
		auto map = GlobalData::mapSexType();
		for (auto it = map.begin(); it != map.end(); it++)
		{
			editor->addItem(it.value(), it.key());
		}
	}
	else
	{
		auto map = GlobalData::mapSampleCupType();
		for (auto it = map.begin(); it != map.end(); it++)
		{
			editor->addItem(it.value(), it.key());
		}
	}


    editor->setView(new  QListView());
    return editor;
}

void ComboxDelegate::setEditorData(QWidget *editor,
                                   const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
	//comboBox->resize(120, 20);
    int tindex = comboBox->findText(text);
    comboBox->setCurrentIndex(tindex);
}

void ComboxDelegate::setModelData(QWidget *editor,
                                  QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
	//comboBox->resize(120, 20);

    QString text = comboBox->currentText()+","+comboBox->currentData().toString();
    model->setData(index, text, Qt::EditRole);
}

void ComboxDelegate::updateEditorGeometry(QWidget *editor,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
	//editor->resize(120, 20);
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
