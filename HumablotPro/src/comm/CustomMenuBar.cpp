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
	// ��д�����¼�
	void paintEvent(QPaintEvent* event) override
	{
		QPainter painter(this);
		painter.fillRect(rect(), QColor("#ffffff"));   // ���ñ���ɫΪ��ɫ

		QList<QAction*> actions = this->actions();     // ��ȡ���е� QAction
		QFont font(painter.font());
		font.setPointSize(18);                         // ���������СΪ 18

		for (auto action : actions) {
			//QRect r(action->geometry());               // ��ȡ�˵����λ�úͳߴ� 
			//painter.setFont(font);                      // ��������
			//painter.drawText(r, Qt::AlignCenter, action->text());       // ������λ�û����ı�
		}
	}
};