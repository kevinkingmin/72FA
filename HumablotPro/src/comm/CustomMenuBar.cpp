#include <QMenuBar>
#include <QString>
#include <QMouseEvent>
#include <QPainter>
#include <QStylePainter>

class CustomMenuBar : public QMenuBar
{
public:
	CustomMenuBar(QWidget *parent = nullptr) : QMenuBar(parent) {}

protected:
	// 重写绘制事件
	void paintEvent(QPaintEvent* event) override
	{
		QPainter painter(this);
		painter.fillRect(rect(), QColor("#ffffff"));   // 设置背景色为白色

		QList<QAction*> actions = this->actions();     // 获取所有的 QAction
		QFont font(painter.font());
		font.setPointSize(18);                         // 设置字体大小为 18

		for (auto action : actions) {
			//QRect r(action->geometry());               // 获取菜单项的位置和尺寸 
			//painter.setFont(font);                      // 设置字体
			//painter.drawText(r, Qt::AlignCenter, action->text());       // 在中心位置绘制文本
		}
	}
};