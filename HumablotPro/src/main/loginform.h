#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QComboBox>
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>
namespace Ui {
class LogInForm;
}

class LogInForm : public QWidget
{
    Q_OBJECT

public:
    explicit LogInForm(QWidget *parent = nullptr);
    ~LogInForm();

	void comboBoxInit(QComboBox*box, int widthScroll = 25, int height = 30, bool bSheet = false);
	void SetControlText();
signals:
    void sigLogIn(QString, QString);
private slots:
    void on_pushButtonLogIn_clicked();
    void on_pushButtonLogOut_clicked();

private:
    Ui::LogInForm *ui;
    void keyPressEvent(QKeyEvent *event) override {
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                on_pushButtonLogIn_clicked();
            } else {
                // 调用基类的 keyPressEvent 以保持默认行为
                QWidget::keyPressEvent(event);
            }
    }
};

#endif // LOGINFORM_H
