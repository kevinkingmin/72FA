#include "MyMessageBox.h"

#define MESSAGEWIDTH 450  //界面的大小
#define MESSAGEHEIGHT 205
#define TEXTFONTFAMILY "微软雅黑"  //text的字体样式和大小
#define TEXTFONTSIZE 12
#define BUTTONFONTFAMILY "微软雅黑"  //按钮的字体样式和大小
#define BUTTONFONTSIZE 10
#define BUTTONWIDTH 110  //按钮的大小
#define BUTTONHEIGHT 50

MyMessageBox::MyMessageBox(QWidget* parent) :
	QDialog(parent) {
	init();
	setWindowIcon(QIcon(":/favicon.ico"));
}

MyMessageBox::MyMessageBox(Icon icon, const QString& title, const QString& text, StandardButtons buttons, QWidget* parent,  QString btx1, QString btx2) :
	QDialog(parent) {
	g_button_text1 = btx1;
	g_button_text2 = btx2;
	init();
	setTitle(text);
	setIcon(icon);
	setText(title+"\n");
	if (buttons != NoButton)
		setStandardButtons(buttons);

}

MyMessageBox::~MyMessageBox() {}

void MyMessageBox::setTitle(const QString& title) {
	setWindowTitle(title);
	//m_pTitleLabel->setText(title);
}

MyMessageBox::Icon MyMessageBox::icon() const {
	return m_icon;
}

void MyMessageBox::setIcon(MyMessageBox::Icon icon) {
	setIconPixmap(standardIcon(icon));
	m_icon = icon;
}

QPixmap MyMessageBox::iconPixmap() const {
	return *m_pIconLabel->pixmap();
}

void MyMessageBox::setIconPixmap(const QPixmap& pixmap) {
	//    m_pIconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_pIconLabel->setPixmap(pixmap);
	m_icon = NoIcon;
}

QString MyMessageBox::text() const {
	return m_pTextLabel->text();
}

void MyMessageBox::setText(const QString& text) {
	m_pTextLabel->setFont(QFont(TEXTFONTFAMILY, TEXTFONTSIZE));
	// 设置对齐方式为居中对齐
	m_pTextLabel->setAlignment(Qt::AlignCenter);
	m_pTextLabel->setText(text);
}

MyMessageBox::StandardButtons MyMessageBox::standardButtons() const {
	QDialogButtonBox::StandardButtons standardButtons = m_pButtonBox->standardButtons();
	return MyMessageBox::StandardButtons(int(standardButtons));  //不同类型的枚举转换
}

void MyMessageBox::setStandardButtons(StandardButtons buttons) {
	QDialogButtonBox::StandardButtons standardButtons = QDialogButtonBox::StandardButtons(int(buttons));
	m_pButtonBox->setStandardButtons(standardButtons);
	int a = m_pButtonBox->buttons().size();
	if (a > 1)
	{
		m_pButtonBox->buttons()[0]->setText(g_button_text1);
		m_pButtonBox->buttons()[1]->setText(g_button_text2);
		m_pButtonBox->buttons()[1]->setStyleSheet("QPushButton{ background:transparent;color: rgb(255, 255, 255);   border-image: url(:/images/buttonIcon/blackgray_click.png) 0px; border: 1px solid #A6A6A6;border-radius:5px;}");
		m_pButtonBox->buttons()[0]->setStyleSheet("QPushButton{ background:transparent;color: rgb(255, 255, 255);   border-image: url(:/images/buttonIcon/red_button_bg.png) 0px; border: 1px solid #A6A6A6;border-radius:5px;}");
	}
	else
	{
		m_pButtonBox->buttons()[0]->setText(g_button_text1);
		m_pButtonBox->buttons()[0]->setStyleSheet("QPushButton{ background:transparent;color: rgb(255, 255, 255);   border-image: url(:/images/buttonIcon/red_button_bg.png) 0px; border: 1px solid #A6A6A6;border-radius:5px;}");
	}
	//    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));  //上面两句归为一句
	setPushButtonProperty(m_pButtonBox->buttons());
}

MyMessageBox::StandardButton MyMessageBox::standardButton(QAbstractButton* button) const {
	QDialogButtonBox::StandardButton standardButton = m_pButtonBox->standardButton(button);
	return (MyMessageBox::StandardButton)standardButton;  //转化为当前类的StandardButton类型
}

QAbstractButton* MyMessageBox::button(MyMessageBox::StandardButton which) const {
	QDialogButtonBox::StandardButton standardButton = QDialogButtonBox::StandardButton(which);
	return m_pButtonBox->button(standardButton);
}

MyMessageBox::ButtonRole MyMessageBox::buttonRole(QAbstractButton* button) const {
	QDialogButtonBox::ButtonRole buttonRole = m_pButtonBox->buttonRole(button);
	return MyMessageBox::ButtonRole(buttonRole);
}

QAbstractButton* MyMessageBox::clickedButton() const {
	return m_pClickedButton;
}

MyMessageBox::StandardButton MyMessageBox::information(QWidget* parent, const QString& text, QString title, StandardButtons buttons, QString button_text1, QString button_text2) {
	return showMessageBox(parent, Information, text, title, buttons, button_text1, button_text2);
}

MyMessageBox::StandardButton MyMessageBox::question(QWidget* parent, const QString& text, QString title, StandardButtons buttons, QString button_text1, QString button_text2) {
	return showMessageBox(parent, Question, text, title, buttons, button_text1, button_text2);
}

MyMessageBox::StandardButton MyMessageBox::success(QWidget* parent, const QString& text, QString title, StandardButtons buttons, QString button_text1, QString button_text2) {
	return showMessageBox(parent, Success, text, title, buttons, button_text1, button_text2);
}

MyMessageBox::StandardButton MyMessageBox::warning(QWidget* parent, const QString& text, QString title, StandardButtons buttons, QString button_text1, QString button_text2) {
	return showMessageBox(parent, Warning, text, title, buttons, button_text1, button_text2);
}

MyMessageBox::StandardButton MyMessageBox::critical(QWidget* parent, const QString& text, QString title, StandardButtons buttons, QString button_text1, QString button_text2) {
	return showMessageBox(parent, Critical, text, title, buttons, button_text1, button_text2);
}

MyMessageBox::StandardButton MyMessageBox::showMessageBox(QWidget* parent, Icon icon, const QString& text, QString title, StandardButtons buttons,QString btx1,QString btx2) {

	MyMessageBox msgBox(icon, title, text, buttons, parent, btx1, btx2);
	//静态函数只能调用静态函数，setMessageBoxGeometry()必须声明为静态函数
	setMessageBoxGeometry(parent, msgBox);
	if (msgBox.exec() == -1)
		return MyMessageBox::Cancel;
	return msgBox.standardButton(msgBox.clickedButton());
}

void MyMessageBox::setMessageBoxGeometry(QWidget* parent, MyMessageBox& msgBox) {
	//QRect rect;
	//if (parent == NULL)
	//{
	//	//rect.x = 100;
	//	//rect.y = 100;
	//	rect.setHeight(100);//= 100;
	//	rect.setWidth(100);// = 100;
	//}
	//else
	//{
	//	rect = parent->geometry();
	//}
	////QRect rect1 = parent->geometry();
	//QDesktopWidget *desktop = QApplication::desktop();
	//int desktop_width = desktop->width();
	//int desktop_height = desktop->height();
	//int x = ((desktop_width - 0) / 2)-(MESSAGEWIDTH/2) -25;
	//int y =  ((desktop_height - 0) / 2)- (MESSAGEHEIGHT/2) -25;
	//msgBox.setGeometry(x, y, MESSAGEWIDTH, MESSAGEHEIGHT);
	//msgBox.move(x, y);
	// 获取屏幕的几何信息
	QDesktopWidget *desktop = QApplication::desktop();
	int screenWidth = desktop->width();
	int screenHeight = desktop->height();
	// 计算弹窗的中心位置
	int x = (screenWidth - msgBox.width()) / 2;
	int y = (screenHeight - msgBox.height()) / 2;
	// 设置弹窗的位置
	msgBox.move(x/2+50, y-200);
}

void MyMessageBox::slotPushButtonClicked(QAbstractButton* button) {
	setClickedButton(button);
	finalize(button);
	close();
}

void MyMessageBox::init() {

	resize(QSize(MESSAGEWIDTH, MESSAGEHEIGHT));
	//setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
	setWindowTitle("MessageInfo");
	setWindowIcon(QIcon(":/images/buttonIcon/icon.png"));
	//对于继承的QDialog，其Flags必须包含Qt::Dialog，不能自定义CustomizeWindowHint
	//否则在构造中指定了parent之后会出现：标题栏消失以及窗口不在正中间
	//setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);  //设置右上角按钮
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);  //去掉标题栏右上角的问号
	//setAttribute(Qt::WA_DeleteOnClose);                                   //关闭窗口时将窗口释放掉即释放内存
	m_pIconLabel = new QLabel(this);
	m_pIconLabel->setObjectName(QLatin1String("iconLabel"));
	m_pIconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);  //图标不可拉伸和缩小，固定大小
	m_pIconLabel->setStyleSheet("color: rgb(222,222, 222); 	padding:15px;      top: -10px; font-family:微软雅黑;   border: 50px ;font-weight: bold;");
	m_pTitleLabel = new QLabel(this);
	m_pTitleLabel->setObjectName(QLatin1String("titleLabel"));
	m_pTitleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);  //图标不可拉伸和缩小，固定大小
	m_pTitleLabel->setStyleSheet("color: rgb(222,222, 222); 	  	padding - top: 0px;    font-family:微软雅黑;   border: 50px ;font-weight: bold;");
	m_pTitleLabel->setVisible(false);
	m_pTextLabel = new QLabel(this);
	m_pTextLabel->setObjectName(QLatin1String("textLabel"));
	m_pTextLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);  //label中的内容可用鼠标选择文本复制，链接激活
	m_pTextLabel->setOpenExternalLinks(true);                           //label中的内容若为链接，可直接点击打开
	m_pTextLabel->setStyleSheet("color: rgb(22,22, 22);    font-family:微软雅黑;   border: 50px ;font-weight: bold;");
	m_pLineLabel = new QLabel(this);
	m_pLineLabel->setText("—————————————————————————————————————————————————————————————\n\r\n");
	m_pLineLabel->setStyleSheet("color: rgb(222,222, 222);  	margin-top:-50px;  font-family:微软雅黑;  	font-size: 16px; font-weight: bold;");
	m_pLineLabel->setFrameStyle(QFrame::HLine | QFrame::Sunken);  //Sunken:凹陷，Raised：凸起
	m_pButtonBox = new QDialogButtonBox(this);                    //默认按钮为水平布局Qt::Horizontal
	m_pButtonBox->setObjectName(QLatin1String("buttonBox"));
	connect(m_pButtonBox, &QDialogButtonBox::clicked, this, &MyMessageBox::slotPushButtonClicked);
	setupLayout();
	setModal(true);
	//setStyleSheet("QDialog{background-color:rgb(255 , 255 , 255);}"
	//	"QPushButton{ background:transparent;color: rgb(255, 255, 255);   	border-image: url(:/images/buttonIcon/blackgray_click.png) 0px; border: 1px solid #A6A6A6;border-radius:5px;}"
	//	"QPushButton:hover{color:white;background-color:transparent;border-radius:5px;border: 0px}"
	//	"QLabel{color: rgb(122,122, 122);    font-family:微软雅黑;   border: 50px ;font-weight: bold;}"
	//	"QPushButton#btnOK:pressed{padding-left:0px;padding-top:0px;background-color:transparent;}");
	//m_pButtonBox->buttons()[0]->setEnabled(false);
}

void MyMessageBox::setupLayout() {
	QVBoxLayout* HLay = new QVBoxLayout;
	HLay->addWidget(m_pTitleLabel, 1, Qt::AlignTop);
	HLay->addWidget(m_pLineLabel, 2,  Qt::AlignTop );
	HLay->addWidget(m_pIconLabel, 3, Qt::AlignVCenter | Qt::AlignTop| Qt::AlignHCenter);
	HLay->addWidget(m_pTextLabel, 4, Qt::AlignVCenter | Qt::AlignTop | Qt::AlignHCenter);
	QHBoxLayout* HLay1 = new QHBoxLayout;
	HLay1->addWidget(m_pButtonBox, 1, Qt::AlignVCenter | Qt::AlignTop | Qt::AlignHCenter);
	//HLay->addLayout(HLay1,6);
	//QMargins margin;
	//margin.setRight(19);
	//HLay1->setContentsMargins(margin);  //调节按钮不要太靠右
	QVBoxLayout* VLay = new QVBoxLayout;
	VLay->addLayout(HLay, 1);
	//VLay->addWidget(m_pLineLabel, 1);
	VLay->addLayout(HLay1, 2);
	VLay->setSpacing(5);
	setLayout(VLay);
}

QPixmap MyMessageBox::standardIcon(Icon icon) {
	QPixmap pixmap;
	switch (icon) {
	case MyMessageBox::Information:
		pixmap.load(":/images/buttonIcon/tip.png");
		break;
	case MyMessageBox::Question:
		pixmap.load(":/images/buttonIcon/wen.png");
		break;
	case MyMessageBox::Success:
		pixmap.load(":/new/prefix1/Image/Success.png");
		break;
	case MyMessageBox::Warning:
		pixmap.load(":/images/buttonIcon/jingshi.png");
		break;
	case MyMessageBox::Critical:
		pixmap.load(":/new/prefix1/Image/Critical.png");
		break;
	default:
		break;
	}
	if (!pixmap.isNull())
		return pixmap;
	return QPixmap();
}

void MyMessageBox::setClickedButton(QAbstractButton* button) {
	m_pClickedButton = button;
}

void MyMessageBox::finalize(QAbstractButton* button) {
	int dialogCode = dialogCodeForButton(button);
	if (dialogCode == QDialog::Accepted) {
		emit accept();
	}
	else if (dialogCode == QDialog::Rejected) {
		emit reject();
	}
}

int MyMessageBox::dialogCodeForButton(QAbstractButton* button) const {
	switch (buttonRole(button)) {
	case MyMessageBox::AcceptRole:
	case MyMessageBox::YesRole:
		return QDialog::Accepted;
	case MyMessageBox::RejectRole:
	case MyMessageBox::NoRole:
		return QDialog::Rejected;
	default:
		return -1;
	}
}

void MyMessageBox::setPushButtonProperty(QList<QAbstractButton*> buttonList) {
	for (int i = 0; i < buttonList.size(); i++) {
		QPushButton* pushButton = qobject_cast<QPushButton*>(buttonList.at(i));
		pushButton->setMinimumSize(BUTTONWIDTH, BUTTONHEIGHT);
		pushButton->setFont(QFont(BUTTONFONTFAMILY, BUTTONFONTSIZE));
	}
}

