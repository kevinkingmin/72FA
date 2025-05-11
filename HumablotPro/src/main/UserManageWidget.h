#pragma once

#include <QWidget>
#include "ui_UserManageWidget.h"
#include <QSqlQuery>
#include <QSqlTableModel>

class UserManageWidget : public QWidget
{
	Q_OBJECT

public:
	UserManageWidget(QWidget *parent ,int userFlage, QString userName);
	~UserManageWidget();
	void ShowTableWidget_Users();
private slots:
	void on_tableWidget_Group_cellClicked();
	void on_tableWidget_Users_cellClicked();
	void on_Add_Button_clicked();
	void on_Modify_Button_clicked();
	void on_Delete_Button_clicked();

private:
	Ui::UserManageWidget ui;
	int m_strGroup_ID;
	int m_SelectGroupId;
	int pkid;
	QString m_str_ID;
	int m_user_type = 3;
	QString m_userName = "";
	QString LoginName;
	QString uPassword;
	QSqlQuery m_GroupQuery;
	QSqlQuery m_UsersQuery;
	void InitGroupsTableWidget();
	void InitUsersValuesTableWidget();
	void addGroupContent(int row, int column, QString content);
	void addUsersContent(int row, int column, QString content);
public:
	QString g_language_type = "";
};
