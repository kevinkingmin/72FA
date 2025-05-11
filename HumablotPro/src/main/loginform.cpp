#include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include "../comm/Global.h"
#include <QDateTime>
#include <QMenuBar>
#include <qt_windows.h>
#include <windowsx.h>  //提供消息关键字的识别
#include <QSharedMemory>
#include "src/types/HumaClia2000.h"
#include <QSettings>
#include "../Include/Instrument/Instrument.h"
#include "src/comm/GlobalData.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QListView>
#include <QStandardItemModel>
#include <list>
#include <QDir>
#include "../model/GetLanguageCls.h"
#include "src/main/subDialog/MyMessageBox.h"

LogInForm::LogInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInForm)
{
    ui->setupUi(this);
	ui->comboBox_UserName->setEditable(true);
	//ui->comboBox_UserName->setcon
	//ui->lineEditUserName->setVisible(false);
	bool bResult;
	auto dao1 = AnalysisUIDao::instance();
	QString select_login_name_list_sql = QString("select  login_name from t_login_name_info order by pkid desc");
	auto select_login_name_info = dao1->SelectRecord(&bResult, select_login_name_list_sql);
	QString  user_name = "";

	int users_count = 0;
	while (select_login_name_info.next())
	{
		user_name = select_login_name_info.value("login_name").toString();
		ui->comboBox_UserName->addItem(user_name);
		users_count++;
	}

	if (users_count == 0)
	{
		ui->comboBox_UserName->addItem("user"); 
	}

	ui->comboBox_UserName->lineEdit()->setAlignment(Qt::AlignLeft);

	// 连接信号到槽
	connect(ui->comboBox_UserName, QOverload<const QString &>::of(&QComboBox::activated), [=](const QString &text) {
		QString userid = text;
		QString password = "";
		// 处理用户选择的操作
		if (userid != "admin")
		{
			bool bResult1;
			auto dao2 = AnalysisUIDao::instance();
			//查询密码
			password = dao2->SelectTargePassword(&bResult1, userid);
			ui->lineEditPassWord->setText(password);
		}
		else
		{
			ui->lineEditPassWord->setText("");
		}
	});

	//comboBoxInit(ui->comboBox_UserName, 25, 39, false);
	ui->widgetLogIn->resize(765, ui->widgetLogIn->height());
	ui->labelVersionInfo->setText("版本：V1.0.0.2  @2023/09/14");//->"版本：V1.0.0.1  @2023/06 / 12"
	ui->lineEditPassWord->setAlignment(Qt::AlignLeft);
	//调试图片分析
	int debug_status = 1;
	if (debug_status)
	{
		ui->pushButton->setVisible(false);
	}
	else
	{
		ui->pushButton->setVisible(true);
	}
	SetControlText();

	//ui->pushButton->setVisible(true);
	ui->pushButton->setVisible(false);
}

void LogInForm::SetControlText()
{
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	QString language_type = dao->SelectTargetValueDes(&bResult, "20005");
	GlobalData::setLanguageType(language_type);
	bResult = false;
	QString user_name_info = GlobalData::LoadLanguageInfo(language_type, "K1004");//.GetLanguagInfo("K1001");
	QString password_info = GlobalData::LoadLanguageInfo(language_type, "KPassword");
	QString TitleLoginKTitle = GlobalData::LoadLanguageInfo(language_type, "KTitle");
	QString TitleLoginK1001 = GlobalData::LoadLanguageInfo(language_type, "K1001");
	QString KCampany = GlobalData::LoadLanguageInfo(language_type, "KCampany");
	QString KVersion = GlobalData::LoadLanguageInfo(language_type, "KVersion");
	ui->labelLogInUserName->setText(user_name_info);
	ui->labelLogInPasssord->setText(password_info);
	ui->labelTitleLogin->setText(TitleLoginKTitle);
	ui->labelLogIn->setText(TitleLoginK1001);
	ui->pushButtonLogIn->setText(GlobalData::LoadLanguageInfo(language_type, "K1002"));
	ui->pushButtonLogOut->setText(GlobalData::LoadLanguageInfo(language_type, "K1003"));
	ui->labelVersionInfo->setText(KVersion);
	ui->labelCampanyInfo->setText(GlobalData::LoadLanguageInfo(language_type, "KCampany"));
}

void LogInForm::comboBoxInit(QComboBox*box, int widthScroll, int height, bool bSheet)
{
	//显示居中
	QLineEdit*lineEdit = box->lineEdit();
	if (lineEdit == 0)
	{
		lineEdit = new QLineEdit(box);
		lineEdit->setObjectName("lintEditAdptive");
		lineEdit->setReadOnly(true);
		lineEdit->setAlignment(Qt::AlignCenter);
		lineEdit->setFocusPolicy(Qt::NoFocus);
		QLineEdit::connect(lineEdit, &QLineEdit::selectionChanged, [=] {
			lineEdit->deselect();
			box->showPopup();
		});
		box->setLineEdit(lineEdit);
	}
	if (bSheet)//是否设置样式
	{
		QString sheet = QString("QComboBox{\
            margin:2px;\
            background: rgba(0,0,0,0);\
            border: 1px solid #C0C4CC;\
            border-radius: 4px;\
            padding-left:%2px;\
            }QComboBox::drop-down {width:%2px;}\
            QComboBox QAbstractItemView {background-color:rgba(0, 0, 0, 0);}\
            QComboBox QAbstractItemView::item {height: 130px;}\
            QComboBox QAbstractScrollArea QScrollBar:vertical { width: %2px; }")
			.arg(height).arg(widthScroll);

		box->setStyleSheet(sheet);
		box->setView(new QListView());

		QString objectName = box->objectName() + "Widget";
		QWidget*parent = qobject_cast<QWidget*>(box->parent());
		if (parent && parent->objectName() != objectName) //  避免反复生成
		{
			QWidget* pWidget = new QWidget(parent); //创建一个widget
			pWidget->setObjectName(objectName);
			QRect rect = box->geometry();
			pWidget->setGeometry(rect);
			box->setParent(pWidget);//更改父窗口为pWidget
			box->move(0, 0);
			pWidget->setStyleSheet("QWidget{background-color:rgba(225, 225, 225, 255);}");
		}
	}

	//设置字体
	QFont font = box->font();
	for (auto w : box->findChildren<QWidget*>())
	{
		w->setFont(font);
	}
	//下拉列表居中
	QStandardItemModel* model = static_cast<QStandardItemModel*>(box->view()->model());
	if (model)
	{
		for (int i = 0; i < model->rowCount(); i++)
		{
			if (model->item(i))
				model->item(i)->setTextAlignment(Qt::AlignCenter);
		}
	}

};

LogInForm::~LogInForm()
{
    delete ui;
}




void LogInForm::on_pushButtonLogIn_clicked()
{
    //emit sigLogIn("admin", "1111");//测试阶段
	QString userid = ui->comboBox_UserName->currentText();//ui->lineEditUserName->text();
	QString password = ui->lineEditPassWord->text();
	if (userid.length() > 16)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1318"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (password.length() > 9)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1319"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
    emit sigLogIn(userid, password);
	//ui->lineEditUserName->setText("");
	ui->lineEditPassWord->setText("");
}

void LogInForm::on_pushButtonLogOut_clicked()
{
    int ret = MyMessageBox::question(this,tr("tip"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1320"), MyMessageBox::Yes| MyMessageBox::No, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1134"));
    if (ret == MyMessageBox::Yes){
        qApp->quit();
    }
}
