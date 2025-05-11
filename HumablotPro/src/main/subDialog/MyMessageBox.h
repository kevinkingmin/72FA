#ifndef MyMessageBox_H
#define MyMessageBox_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMetaEnum>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

#include <qdesktopwidget.h>


class MyMessageBox : public QDialog {
	Q_OBJECT

public:
	enum Icon {
		NoIcon = 0,
		Information = 1,
		Question = 2,
		Success = 3,
		Warning = 4,
		Critical = 5
	};
	Q_ENUM(Icon)  //ʹ��Q_ENUMע��ö��

		enum StandardButton {
		//���������� QDialogButtonBox::StandardButton һ�£��ڴ�����ťʱ���ܻ��õ� & ����
		NoButton = 0x00000000,
		Ok = 0x00000400,
		Save = 0x00000800,
		SaveAll = 0x00001000,
		Open = 0x00002000,
		Yes = 0x00004000,
		YesToAll = 0x00008000,
		No = 0x00010000,
		NoToAll = 0x00020000,
		Abort = 0x00040000,
		Retry = 0x00080000,
		Ignore = 0x00100000,
		Close = 0x00200000,
		Cancel = 0x00400000,
		Discard = 0x00800000,
		Help = 0x01000000,
		Apply = 0x02000000,
		Reset = 0x04000000,
		RestoreDefaults = 0x08000000,

		FirstButton = Ok,
		LastButton = RestoreDefaults
	};
	Q_ENUM(StandardButton)
		Q_DECLARE_FLAGS(StandardButtons, StandardButton)
		Q_FLAG(StandardButtons)

		enum ButtonRole {
		//������ QDialogButtonBox::ButtonRole һ��
		InvalidRole = -1,
		AcceptRole,
		RejectRole,
		DestructiveRole,
		ActionRole,
		HelpRole,
		YesRole,
		NoRole,
		ResetRole,
		ApplyRole,

		NRoles
	};

	explicit MyMessageBox(QWidget* parent = nullptr);
	MyMessageBox(Icon icon, const QString& title, const QString& text, StandardButtons buttons,
		QWidget* parent ,QString btx1,QString btx2);  //���캯����Ĭ��ֵ��Ҫ�ź���
	~MyMessageBox();

	void setTitle(const QString& title);

	Icon icon() const;
	void setIcon(Icon icon);

	QPixmap iconPixmap() const;
	void setIconPixmap(const QPixmap& pixmap);

	QString text() const;
	void setText(const QString& text);

	StandardButtons standardButtons() const;
	void setStandardButtons(StandardButtons buttons);
	StandardButton standardButton(QAbstractButton* button) const;
	QAbstractButton* button(StandardButton which) const;

	ButtonRole buttonRole(QAbstractButton* button) const;

	QAbstractButton* clickedButton() const;

	//static StandardButton information(QWidget* parent, const QString& text, QString title = "Message", StandardButtons buttons = Ok);
	//static StandardButton question(QWidget* parent, const QString& text, QString title = "Message", StandardButtons buttons = StandardButtons(Yes | No));
	//static StandardButton success(QWidget* parent, const QString& text, QString title = "Message", StandardButtons buttons = Ok);
	//static StandardButton warning(QWidget* parent, const QString& text, QString title = "Message", StandardButtons buttons = Ok);
	//static StandardButton critical(QWidget* parent, const QString& text, QString title = "Message", StandardButtons buttons = Ok);


	static StandardButton information(QWidget* parent, const QString& text, QString title , StandardButtons buttons , QString button_text1, QString button_text2);
	static StandardButton question(QWidget* parent, const QString& text, QString title , StandardButtons buttons , QString button_text1, QString button_text2);
	static StandardButton success(QWidget* parent, const QString& text, QString title , StandardButtons buttons , QString button_text1, QString button_text2);
	static StandardButton warning(QWidget* parent, const QString& text, QString title , StandardButtons buttons , QString button_text1, QString button_text2);
	static StandardButton critical(QWidget* parent, const QString& text, QString title , StandardButtons buttons ,  QString button_text1, QString button_text2);



	static StandardButton showMessageBox(QWidget* parent, Icon icon, const QString& text, QString title, StandardButtons buttons, QString btx1, QString btx2);

	static void setMessageBoxGeometry(QWidget* parent, MyMessageBox& msgBox);

private slots:
	void slotPushButtonClicked(QAbstractButton* button);

private:
	void init();
	void setupLayout();
	QPixmap standardIcon(Icon icon);
	void setClickedButton(QAbstractButton* button);
	void finalize(QAbstractButton* button);
	int dialogCodeForButton(QAbstractButton* button) const;
	void setPushButtonProperty(QList<QAbstractButton*> buttonList);

public:
		QString g_button_text1;
		QString g_button_text2;
private:
	QLabel* m_pIconLabel;
	MyMessageBox::Icon m_icon;
	QLabel* m_pTextLabel;
	QLabel* m_pLineLabel;
	QLabel* m_pTitleLabel;
	QDialogButtonBox* m_pButtonBox;
	QAbstractButton* m_pClickedButton;






};

//��ȫ������ط�ʹ��"|"�����������Զ����ö��������Ҫʹ��Q_DECLARE_OPERATORS_FOR_FLAGS��
Q_DECLARE_OPERATORS_FOR_FLAGS(MyMessageBox::StandardButtons)

#endif  // MyMessageBox_H

