#ifndef LSMESSAGEBOX_H
#define LSMESSAGEBOX_H

#include <QWidget>
#include <QMessageBox>
#include <QResizeEvent>
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

class LSMessageBox : public QMessageBox
{
	Q_OBJECT
public:
	explicit LSMessageBox(QWidget *parent = 0);
	void setMySize(int width, int height);
	void init();

signals:

public slots:

protected:
	void resizeEvent(QResizeEvent *event);

private:
	int _width;
	int _height;
};

#endif // LSMESSAGEBOX_H