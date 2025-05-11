#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QPushButton>
#include <QString>
class QLabel;
class QVBoxLayout;
class CustomButton:public QPushButton
{
public:
    CustomButton(QWidget *parent = nullptr);
    virtual ~CustomButton();
    void setUpText(const QString &upText);
    void setReagentName(const QString &reagentName);
	QString getReagentName();
	int getBtnId();
    void setVolumn(const QString &volumn);
    QString getVolumn() const;
    void setTimeText(const QString &timeText);
    QString getTimeText();
    void setPixPath(const QString &pixPath);
    void setLblPixSize(int width,int height);
    void reset(const QString &pixPath);
	void setBtnId(int id);

protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    int getChineseCount(const QString &str);
private:
	int _btn_id;
    QString _upText;
    QString _reagentName;
    QString _volumn;
    QString _timeText;
    QString _pixPath;    
    QLabel *_lblUp;
	QLabel *_lblSpace;
    QLabel *_lblPix;
    QLabel *_lblReagent;
    QLabel *_lblVolumn;
    QLabel *_lblTime;
    QVBoxLayout *m_vLay;
};

#endif // CUSTOMBUTTON_H
