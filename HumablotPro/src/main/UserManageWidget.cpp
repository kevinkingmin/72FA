#include "..\include\precomp\precompile.h"
#include "UserManageWidget.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QtXml> 
#include<QFileDialog>
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QLineEdit>
#include "../DAO/src/user/UserDao.h"
#include "src/main/subDialog/MyMessageBox.h"

UserManageWidget::UserManageWidget(QWidget *parent, int userFlage,QString userName)
	: QWidget(parent)
{
	setAttribute(Qt::WA_ShowModal, true);
	ui.setupUi(this);


	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");

	m_user_type = userFlage;
	m_userName = userName;
	//清空列表
	ui.tableWidget_Users->setRowCount(0);
	ui.tableWidget_Group->setRowCount(0);
	ui.tableWidget_Group->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//隔行变色
	ui.tableWidget_Users->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_Users->setShowGrid(false);

	//隔行变色
	ui.tableWidget_Group->setAlternatingRowColors(true);
	//去掉网格线
	ui.tableWidget_Group->setShowGrid(false);




	InitGroupsTableWidget();
	InitUsersValuesTableWidget();
	if (m_user_type == 3)
	{
		ui.Add_Button->setVisible(false);
		ui.Delete_Button->setVisible(false);
	}
	else
	{
		ui.Add_Button->setVisible(true);
		ui.Delete_Button->setVisible(true);
	}
	ui.lineEditPassword->setEchoMode(QLineEdit::Password);

	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1018");
	ui.label->setText(sz2);
	sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1108");
	ui.Add_Button->setText(sz2);
	sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1109");
	ui.Modify_Button->setText(sz2);
	sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1140");
	ui.Delete_Button->setText(sz2);

	sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1004");
	ui.label_2->setText(sz2);
	sz2 = GlobalData::LoadLanguageInfo(g_language_type, "KPassword");
	ui.label_3->setText(sz2);
}

UserManageWidget::~UserManageWidget()
{
}

void UserManageWidget::InitUsersValuesTableWidget()
{
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Users->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Users->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Users->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Users->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	ui.tableWidget_Users->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	ui.tableWidget_Users->setSortingEnabled(false);





}

void UserManageWidget::InitGroupsTableWidget()
{
	ui.tableWidget_Group->setRowCount(0);
	//不显示左边默认自带序列号
	QHeaderView* headerView = ui.tableWidget_Group->verticalHeader();
	headerView->setHidden(true);
	//使行列头自适应宽度，最后一列将会填充空白部分
	ui.tableWidget_Group->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget_Group->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	ui.tableWidget_Group->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择膜式，选择单行
	//ui.tableWidget_Rule->setEditTriggers(QAbstractItemView::NoEditTriggers);	//列表不可编辑
	//判断登录是否成功
	QString GroupName;
	//DB中取Testitems表数据
	bool bResult = true;
	auto dao = UserDao::instance();
	//QString userid1 = "root";
	//QString password1 = "mbjbios";
	QString sql = "";

	QStringList headerString;
	QStringList headerString1;
	QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1187");
	headerString << sz1;
	ui.tableWidget_Group->setHorizontalHeaderLabels(headerString);

	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1004");
	QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "KPassword");
	headerString1 << "NO" << sz2 << sz3;
	ui.tableWidget_Users->setHorizontalHeaderLabels(headerString1);

	if (m_user_type == 1)
	{
		//sql = QString("SELECT DISTINCT A.GroupID,B.GroupName from tuser A ,tusergroup B WHERE B.ID = A.GroupID and A.GroupID<>1");
		sql = QString("SELECT DISTINCT A.GroupID,B.GroupName from tuser A ,tusergroup B WHERE B.ID = A.GroupID ");
	}else if(m_user_type == 2)//工程师
	{
		sql = QString("SELECT DISTINCT A.GroupID,B.GroupName from tuser A ,tusergroup B WHERE B.ID = A.GroupID and (B.ID=3 or (B.ID=2 and LoginName='%1')) ORDER BY A.GroupID asc").arg(m_userName);
	}
	else if(m_user_type == 3)//普通用户
	{
		sql = QString("SELECT DISTINCT A.GroupID,B.GroupName from tuser A ,tusergroup B WHERE B.ID = A.GroupID  and A.LoginName='%1'").arg(m_userName);
	}
	//QString sql = QString("SELECT DISTINCT A.GroupID,B.GroupName from tuser A ,tusergroup B WHERE B.ID = A.GroupID ");//("select * from tuser where LoginName='%1' and uPassword='%2'").arg(userid).arg(password);
	m_GroupQuery = dao->SelectRecord(&bResult, sql);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1349"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}

	int row = 0;
	while (m_GroupQuery.next())
	{
		GroupName = m_GroupQuery.value("GroupName").toString();
		ui.tableWidget_Group->insertRow(row);
		addGroupContent(row, 0, GroupName);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget_Group->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
}

void UserManageWidget::addGroupContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget_Group->setItem(row, column, item);
}

void UserManageWidget::on_tableWidget_Group_cellClicked()
{
	//清空列表
	ui.tableWidget_Users->setRowCount(0);
	int intRow = ui.tableWidget_Group->currentRow();//获取选中的行
	if (m_GroupQuery.size() == 0)
		return;
	m_GroupQuery.seek(intRow);
	m_SelectGroupId = m_GroupQuery.value("GroupID").toInt();
	ShowTableWidget_Users();
}
void UserManageWidget::ShowTableWidget_Users()
{
	//清空列表
	ui.tableWidget_Users->setRowCount(0);
	QString strValue;
	bool bResult = true;
	auto dao = AnalysisUIDao::instance();
	QString sql = "";

	if (m_user_type == 1)
	{
		sql.sprintf("select * from tuser where GroupID =%d order by ID asc", m_SelectGroupId);
	}else if(m_user_type ==2)
	{
		if (m_SelectGroupId == 2)
		{
			sql = QString("select * from tuser where (GroupId=%1 and LoginName='%2')").arg(m_SelectGroupId).arg(m_userName);
		}
		if (m_SelectGroupId == 3)
		{
			sql = QString("select * from tuser where (GroupId=%1)").arg(m_SelectGroupId);
		}
	}
	else if (m_user_type == 3)
	{
		sql = QString("select * from tuser where (LoginName='%1') and GroupId=3 ").arg(m_userName);
	}

	m_UsersQuery = dao->SelectRecord(&bResult, sql);
	if (bResult == false)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1350"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (m_UsersQuery.size() == 0)
	{
		//QMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), "数据库表中缺少测试膜条数据！", QMessageBox::Ok);
		return;
	}

	int row = 0;
	QString sID = "0";
	while (m_UsersQuery.next())
	{
		ui.tableWidget_Users->insertRow(row);
		//ID
		sID = QString::number(row + 1);
		addUsersContent(row, 0, sID);
		//名称
		strValue = m_UsersQuery.value("LoginName").toString();
		addUsersContent(row, 1, strValue);
		//密码
		strValue = m_UsersQuery.value("uPassword").toString();
		addUsersContent(row, 2, strValue);
		row++;
	}
	if (row > 0)
	{
		/*设置让某个单元格或某行选中*/
		//选中单元格 第一行：
		ui.tableWidget_Users->setCurrentCell(0, 0, QItemSelectionModel::Select);
	}
}
void UserManageWidget::addUsersContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget_Users->setItem(row, column, item);
}

void UserManageWidget::on_tableWidget_Users_cellClicked()
{
	int intRow = ui.tableWidget_Users->currentRow();//获取选中的行
	if (m_UsersQuery.size() == 0)
		return;
	m_UsersQuery.seek(intRow);
	m_str_ID = m_UsersQuery.value("ID").toString();
	LoginName = m_UsersQuery.value("LoginName").toString();
	uPassword = m_UsersQuery.value("uPassword").toString();
	int group_id = m_UsersQuery.value("GroupID").toInt();
	
	if (m_user_type == group_id)
	{
		ui.lineEditUserName33->setText(LoginName);
		ui.lineEditUserName33->setEnabled(false);
		ui.lineEditPassword->setText(uPassword);
	}
	else
	{
		ui.lineEditUserName33->setText(LoginName);
		ui.lineEditUserName33->setEnabled(true);
		ui.lineEditPassword->setText(uPassword);
	}

	//ui.lineEditGrayWord
}
void UserManageWidget::on_Add_Button_clicked()
{
	QString UserName = ui.lineEditUserName33->text();
	QString Password = ui.lineEditPassword->text();


	UserName = UserName.replace(" ", "");
	Password = Password.replace(" ", "");

	if (UserName.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1351"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (Password.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1352"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (UserName.length() > 16)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1318"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (Password.length() > 9)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1319"),MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	bool bResult = true;
	QString sql1 = QString("insert into tuser(GroupID,LoginName,uPassword)values(%1,'%2','%3')").arg(m_SelectGroupId).arg(UserName).arg(Password);
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql1);
	if (!bResult)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1301"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	else
	{
		//刷新界面
		ShowTableWidget_Users();
	}
}
void UserManageWidget::on_Modify_Button_clicked()
{

	QString UserName = ui.lineEditUserName33->text();
	QString Password = ui.lineEditPassword->text();

	UserName = UserName.replace(" ", "");
	Password = Password.replace(" ", "");

	if (UserName.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1351"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");

		return;
	}
	if (Password.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1352"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");

		return;
	}



	if (LoginName.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1351"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}
	if (uPassword.length() == 0)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1352"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
		return;
	}



	if (LoginName.length() > 16)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1318"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	if (uPassword.length() > 9)
	{
		MyMessageBox::information(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1319"), MyMessageBox::Ok,GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}
	auto dao = AnalysisUIDao::instance();

	QString LoginName = UserName;//ui.lineEditUserName33->text();
	QString uPassword = Password;//ui.lineEditPassword->text();

	bool bResult = true;
	QString sql = QString("select * from tuser where  LoginName='%1'  and uPassword='%2").arg(LoginName).arg(uPassword);

	QSqlQuery ResultQuery = dao->SelectRecord(&bResult, sql);

	int size = ResultQuery.size();

	if (size > 0)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1353"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"),"");
		return;
	}

	QString sql1 = QString("update tuser set LoginName='%1',uPassword='%2' where ID =%3 ").arg(LoginName).arg(uPassword).arg(m_str_ID);

	dao->SelectRecord(&bResult, sql1);
	if (!bResult)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1294"), MyMessageBox::Ok, "OK", "");
		return;
	}
	else
	{
		//刷新界面
		ShowTableWidget_Users();
	}
}
void UserManageWidget::on_Delete_Button_clicked()
{
	//m_strRuleValues_ID
	bool bResult = true;
	QString sql = "";
	QString LoginName = ui.lineEditUserName33->text();
	if (LoginName == "admin")
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1354"), MyMessageBox::Ok, "OK", "");
		return;
	}
	//sql.sprintf("delete from tuser where ID =%d and LoginName='%s' ", m_str_ID.toInt(), LoginName);
	sql = QString("delete from tuser where ID =%1 and LoginName='%2' ").arg(m_str_ID.toInt()).arg(LoginName);
	auto dao = AnalysisUIDao::instance();
	dao->SelectRecord(&bResult, sql);
	if (!bResult)
	{
		MyMessageBox::warning(this, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1111"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1291"), MyMessageBox::Ok,"OK","");
		return;
	}
	else
	{
		//刷新界面
		ShowTableWidget_Users();
	}
}