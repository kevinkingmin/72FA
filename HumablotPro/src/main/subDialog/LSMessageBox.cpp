//#include "..\Include\Precomp\precompile.h"
//#include "LSMessageBox.h"
#include "LSMessageBox.h"

#define MESSAGEWIDTH 450  //界面的大小
#define MESSAGEHEIGHT 205

LSMessageBox::LSMessageBox(QWidget *parent) :
	QMessageBox(parent),
	_width(0),
	_height(0)
{
	init();
}

void LSMessageBox::init()
{

	resize(QSize(MESSAGEWIDTH, MESSAGEHEIGHT));
	setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
	setWindowTitle("MessageInfo");
	//对于继承的QDialog，其Flags必须包含Qt::Dialog，不能自定义CustomizeWindowHint
	//否则在构造中指定了parent之后会出现：标题栏消失以及窗口不在正中间
	//setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);  //设置右上角按钮
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);  //去掉标题栏右上角的问号
	//setAttribute(Qt::WA_DeleteOnClose);                                   //关闭窗口时将窗口释放掉即释放内存

	//m_pIconLabel = new QLabel(this);
	//m_pIconLabel->setObjectName(QLatin1String("iconLabel"));
	//m_pIconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);  //图标不可拉伸和缩小，固定大小


	//m_pTextLabel = new QLabel(this);
	//m_pTextLabel->setObjectName(QLatin1String("textLabel"));
	//m_pTextLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);  //label中的内容可用鼠标选择文本复制，链接激活
	//m_pTextLabel->setOpenExternalLinks(true);                           //label中的内容若为链接，可直接点击打开


	//m_pLineLabel = new QLabel(this);
	//m_pLineLabel->setText("————————————————————————————\n\r\n");
	//m_pLineLabel->setFrameStyle(QFrame::HLine | QFrame::Sunken);  //Sunken:凹陷，Raised：凸起
	//m_pButtonBox = new QDialogButtonBox(this);                    //默认按钮为水平布局Qt::Horizontal
	//m_pButtonBox->setObjectName(QLatin1String("buttonBox"));
	//connect(m_pButtonBox, &QDialogButtonBox::clicked, this, &MyMessageBox::slotPushButtonClicked);
	//setupLayout();
	setModal(true);
	setStyleSheet("QDialog{background-color:rgb(255 , 255 , 255);}"
		"QPushButton{ background:transparent;color: rgb(255, 255, 255);   	border-image: url(:/images/buttonIcon/blackgray_click.png) 0px;border: 1px solid #A6A6A6;border-radius:5px;}"
		"QPushButton:hover{color:white;background-color:transparent;border-radius:5px;border: 0px}"
		"QLabel{color: rgb(122,122, 122);    font-family:微软雅黑;   border: 50px ;font-weight: bold;}"
		"QPushButton#btnOK:pressed{padding-left:0px;padding-top:0px;background-color:transparent;}");
}

void LSMessageBox::setMySize(int width, int height)
{
	_width = width;
	_height = height;
}

void LSMessageBox::resizeEvent(QResizeEvent *event)
{
	setFixedSize(_width, _height);
}