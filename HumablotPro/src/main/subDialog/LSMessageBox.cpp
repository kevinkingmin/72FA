//#include "..\Include\Precomp\precompile.h"
//#include "LSMessageBox.h"
#include "LSMessageBox.h"

#define MESSAGEWIDTH 450  //����Ĵ�С
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
	//���ڼ̳е�QDialog����Flags�������Qt::Dialog�������Զ���CustomizeWindowHint
	//�����ڹ�����ָ����parent֮�����֣���������ʧ�Լ����ڲ������м�
	//setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);  //�������Ͻǰ�ť
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);  //ȥ�����������Ͻǵ��ʺ�
	//setAttribute(Qt::WA_DeleteOnClose);                                   //�رմ���ʱ�������ͷŵ����ͷ��ڴ�

	//m_pIconLabel = new QLabel(this);
	//m_pIconLabel->setObjectName(QLatin1String("iconLabel"));
	//m_pIconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);  //ͼ�겻���������С���̶���С


	//m_pTextLabel = new QLabel(this);
	//m_pTextLabel->setObjectName(QLatin1String("textLabel"));
	//m_pTextLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);  //label�е����ݿ������ѡ���ı����ƣ����Ӽ���
	//m_pTextLabel->setOpenExternalLinks(true);                           //label�е�������Ϊ���ӣ���ֱ�ӵ����


	//m_pLineLabel = new QLabel(this);
	//m_pLineLabel->setText("��������������������������������������������������������\n\r\n");
	//m_pLineLabel->setFrameStyle(QFrame::HLine | QFrame::Sunken);  //Sunken:���ݣ�Raised��͹��
	//m_pButtonBox = new QDialogButtonBox(this);                    //Ĭ�ϰ�ťΪˮƽ����Qt::Horizontal
	//m_pButtonBox->setObjectName(QLatin1String("buttonBox"));
	//connect(m_pButtonBox, &QDialogButtonBox::clicked, this, &MyMessageBox::slotPushButtonClicked);
	//setupLayout();
	setModal(true);
	setStyleSheet("QDialog{background-color:rgb(255 , 255 , 255);}"
		"QPushButton{ background:transparent;color: rgb(255, 255, 255);   	border-image: url(:/images/buttonIcon/blackgray_click.png) 0px;border: 1px solid #A6A6A6;border-radius:5px;}"
		"QPushButton:hover{color:white;background-color:transparent;border-radius:5px;border: 0px}"
		"QLabel{color: rgb(122,122, 122);    font-family:΢���ź�;   border: 50px ;font-weight: bold;}"
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