#include "CustomLabel1.h"
#include <QPainter>
#include <QStylePainter>
#include "GlobalData.h"

#define LBLWIDTH 38
#define LBLHEIGHT 180
CustomLabel1::CustomLabel1(QWidget *parent):QLabel (parent)
  ,_bgColor("#EEEEEE")
  ,_pos(0)
{
    clear();
}

CustomLabel1::~CustomLabel1()
{    
}


void CustomLabel1::paintEvent(QPaintEvent *)
{
	QStylePainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QString sample_no("");
	QString paper_name("");
	QString sample_no1("");

    QStringList list =  text().split(':');
    if (list.count() == 3)
    {
        sample_no = list[0];
        paper_name = list[1];
        sample_no1 = list[2];
        paper_name = QString("%1\n%2").arg(paper_name).arg(sample_no1);
    }

    QFont font = painter.font();
    font.setPixelSize(19);
    font.setFamily("simsun");
	font.setWeight(90);	
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(225, 225, 225));

    setAutoFillBackground(true);
    setPalette(palette);
    this->setMinimumWidth(LBLWIDTH);
    this->setMaximumWidth(LBLWIDTH);
    this->setMinimumHeight(LBLHEIGHT);
    painter.setFont(font);

	QRect numRect(0, geometry().height() - LBLWIDTH + 15, LBLWIDTH, LBLWIDTH - 15);
	QColor color("#F67D52");
	if (underMouse()) 
		painter.fillRect(numRect, color);
	
	if (_pos <= 36)
	{
        painter.drawText(numRect, Qt::AlignBottom | Qt::AlignHCenter, QString::number(_pos));
	}
	else
	{
        painter.drawText(numRect, Qt::AlignBottom | Qt::AlignHCenter, QString::number(_pos - 36));
	}
	int x = height() - 15;
    int y = height();

	QPixmap pix(x, y);
    QPainter p(&pix);
    pix.fill(QColor(_bgColor));
	int p_position = pix.height() - LBLWIDTH - 0 + 30;
	p.translate(0, p_position);

	p.rotate(-90);
    p.setFont(font);
	p.drawText(pix.rect(), paper_name);
	painter.drawPixmap(0, LBLWIDTH - 55, pix);


	if (sample_no != "")
	{
		int radius = 15;
		painter.drawEllipse(QPoint(18, 15), radius, radius);
		QRect numRect1(7, 5, 20, 20);
		painter.drawText(numRect1, Qt::AlignCenter, sample_no);
	}
}

void CustomLabel1::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit clicked(_pos);
}

int CustomLabel1::getPos() const
{
    return _pos;
}

void CustomLabel1::reset()
{
    _bgColor="#D3D3D3";
    setText("");
}

void CustomLabel1::setBgColor(const QString &bgColor)
{
    _bgColor = bgColor;
}

void CustomLabel1::setPos(int pos)
{
    _pos=pos;
}
