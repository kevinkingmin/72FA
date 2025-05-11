#include <QDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QMenuBar>
#include <QStyleOptionMenuItem>
#include <QPainter>


class CustomMenuBarWidget : public QWidget
{
public:
	explicit CustomMenuBarWidget(QWidget *parent = Q_NULLPTR)
		: QWidget(parent)
		, menuBar(new QMenuBar())
	{
	}

	virtual void paintEvent(QPaintEvent *event) {
		QStyleOptionMenuItem styleOptionMenuItem;
		QIcon icon("path/to/my/icon");
		styleOptionMenuItem.icon = icon;
		styleOptionMenuItem.text = "Hello World!";
		QPainter painter(this);
		menuBar->style()->drawControl(QStyle::CE_MenuBarItem, &styleOptionMenuItem, &painter, menuBar);
	}
private:
	QMenuBar *menuBar;
};