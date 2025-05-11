#pragma once

#include <QWidget>
#include "ui_TestPaper.h"
#include <QMap>


typedef struct {
	QLabel	  *label;
	QCheckBox *checkBox;
	QLineEdit *lineEdit_Name;
	QComboBox * combo_box_rule;
	QLineEdit *lineEdit_Position;

}Item_Control, *LPItem_Control;

typedef struct {
	bool	isNullArea;			//是否为空白区域 
	int     nPostionNo;			//项目所在位置序号(包含空白区域) 
	QString	strItemName;		//项目名称
	int     judgerule;          //判读规则
	double position;            //距离识别点位置

}TestPaper_Item, *LPTestPaper_Item;

class Instrument;


class TestPaper : public QWidget
{
	Q_OBJECT

public:
	TestPaper(QWidget *parent = Q_NULLPTR);
	~TestPaper();

	QString m_strCompany_ID;

	bool m_bModify = false;

	QString m_strTestPaper_ID;

	QMap<QString, int> m_RulesName;

	void Set_UI();

private:
	Ui::TestPaper ui;

	int m_nTotalNumber = 0;
	int m_nNull_Number = 0;
	int m_nItem_Number = 0;

	Item_Control m_Item_Control_Array[31];

	Instrument * _instr;
	QString m_strMachineUID;


	void TestPaper::Set_checkBox_stateChanged(int state, QLineEdit * lineEdit_Name);

	void Set_Item_Control_Array();

	void Set_Controls_visible();

	bool Save_TestPaper_Items();

	void Set_TestPaper_Item(TestPaper_Item& testPaper_Item,int nPostionNo,QCheckBox *checkBox,QLineEdit *lineEdit_Name, QComboBox * combo_box_rule,QLineEdit *lineEdit_Position);

	void Set_Control_Value(
						TestPaper_Item testPaper_Item);

	bool Save_TestPaper_Parameters();

	bool CheckInput();

	void CutOffCheckBoxUpdateUi(int state);


public:
	QString g_language_type = "";

private slots:

	void on_pushButton_Set_clicked();
	void on_pushButton_Save_clicked();
	void on_pushButton_Cancel_clicked();

	void on_checkBox_1_stateChanged(int state);
	void on_checkBox_2_stateChanged(int state);
	void on_checkBox_3_stateChanged(int state);
	void on_checkBox_4_stateChanged(int state);
	void on_checkBox_5_stateChanged(int state);
	void on_checkBox_6_stateChanged(int state);
	void on_checkBox_7_stateChanged(int state);
	void on_checkBox_8_stateChanged(int state);
	void on_checkBox_9_stateChanged(int state);
	void on_checkBox_10_stateChanged(int state);
	void on_checkBox_11_stateChanged(int state);
	void on_checkBox_12_stateChanged(int state);
	void on_checkBox_13_stateChanged(int state);
	void on_checkBox_14_stateChanged(int state);
	void on_checkBox_15_stateChanged(int state);
	void on_checkBox_16_stateChanged(int state);
	void on_checkBox_17_stateChanged(int state);
	void on_checkBox_18_stateChanged(int state);
	void on_checkBox_19_stateChanged(int state);
	void on_checkBox_20_stateChanged(int state);
	void on_checkBox_21_stateChanged(int state);
	void on_checkBox_22_stateChanged(int state);
	void on_checkBox_23_stateChanged(int state);
	void on_checkBox_24_stateChanged(int state);
	void on_checkBox_25_stateChanged(int state);
	void on_checkBox_26_stateChanged(int state);
	void on_checkBox_27_stateChanged(int state);
	void on_checkBox_28_stateChanged(int state);
	void on_checkBox_29_stateChanged(int state);
	void on_checkBox_30_stateChanged(int state);
	void on_checkBox_CutOff_stateChanged(int state);

	//void on_pushButton_PickColor_clicked();
	void color_slots_func();

signals:
	void SetRefresh(bool bFlag);
};
