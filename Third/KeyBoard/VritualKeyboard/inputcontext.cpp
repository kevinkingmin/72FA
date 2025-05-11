#include <QtDebug>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QMainWindow>
#include <QInputDialog>
#include "inputcontext.h"
#include "googlepinyin.h"

#define WINDOW_HEIGHT QApplication::desktop()->height()
#define WINDOW_WIDTH  QApplication::desktop()->width()

static InputContext *instance = NULL;

InputContextPrivate::InputContextPrivate() :
    KeyBoard(0),
    NumKeyBoard(0)
{
}

InputContextPrivate::~InputContextPrivate()
{
    if (KeyBoard)
        delete KeyBoard;
    if (NumKeyBoard)
        delete NumKeyBoard;
}

InputContext* InputContext::Instance()
{
    return instance;
}

InputContext::InputContext() :
    QPlatformInputContext()
{
    d = new InputContextPrivate();
    instance = this;
}

InputContext::~InputContext()
{
}

bool InputContext::isValid() const
{
    return true;
}

QRectF InputContext::keyboardRect() const
{

    if (d->KeyBoard->isVisible()){
        return (d->KeyBoard) ? d->KeyBoard->rect() : QRectF();
    } else if (d->NumKeyBoard->isVisible()){
        return (d->NumKeyBoard) ? d->NumKeyBoard->rect() : QRectF();
    } else {
        return QRectF();
    }
}

void InputContext::showInputPanel()
{
    if (!d->KeyBoard)
    {
        d->KeyBoard = new KeyboardForm();
        connect(d->KeyBoard, SIGNAL(sendKeyToFocusItem(QString)), &d->keyEventDispatcher, SLOT(sendKeyToFocusItem(QString)));
    }
    if (!d->NumKeyBoard)
    {
        d->NumKeyBoard = new KeyboardFormNum();
        connect(d->NumKeyBoard, SIGNAL(sendKeyToFocusItem(QString)), &d->keyEventDispatcher, SLOT(sendKeyToFocusItem(QString)));
    }
    bool show = _object->property("showFull").toBool();
    if (!show){
        if (d->KeyBoard->isVisible()){
            d->KeyBoard->hide();
        }
        if (d->NumKeyBoard->isHidden()){
            d->NumKeyBoard->show();
        }
        qDebug()<<__FUNCTION__<<show;
        int keyboardX = curWidgetPos.x();
        int keyboardY = curWidgetPos.y()+curWidgetRect.height()+2;

        if ((keyboardX + d->NumKeyBoard->width()) > WINDOW_WIDTH) {
            keyboardX = WINDOW_WIDTH - d->NumKeyBoard->width() -2;
        } else {
            keyboardX = curWidgetPos.x();
        }
        if ((keyboardY + d->NumKeyBoard->height()) > WINDOW_HEIGHT) {
            keyboardY = curWidgetPos.y()-d->NumKeyBoard->height()-2;
        } else {
            keyboardY = curWidgetPos.y()+curWidgetRect.height()+2;
        }
        d->NumKeyBoard->setGeometry(keyboardX,keyboardY,d->NumKeyBoard->width(),d->NumKeyBoard->height());
    } else {
        if (d->NumKeyBoard->isVisible()){
            d->NumKeyBoard->hide();
        }
        if (d->KeyBoard->isHidden()){
            d->KeyBoard->show();
        }
        int keyboardX = curWidgetPos.x();
        int keyboardY = curWidgetPos.y()+curWidgetRect.height()+2;

        if ((keyboardX + d->KeyBoard->width()) > WINDOW_WIDTH) {
            keyboardX = WINDOW_WIDTH - d->KeyBoard->width() -2;
        } else {
            keyboardX = curWidgetPos.x();
        }
        if ((keyboardY + d->KeyBoard->height()) > WINDOW_HEIGHT) {
            keyboardY = curWidgetPos.y()-d->KeyBoard->height()-2;
        } else {
            keyboardY = curWidgetPos.y()+curWidgetRect.height()+2;
        }
        d->KeyBoard->setGeometry(keyboardX,keyboardY,d->KeyBoard->width(),d->KeyBoard->height());
    }

    QPlatformInputContext::showInputPanel();
}

void InputContext::hideInputPanel()
{
    if (d->KeyBoard)
    {
        d->KeyBoard->hide();
    }
    if (d->NumKeyBoard)
    {
        d->NumKeyBoard->hide();
    }

    QPlatformInputContext::hideInputPanel();
}

bool InputContext::isInputPanelVisible() const
{
    if ((d->KeyBoard && d->KeyBoard->isVisible()) ||
        (d->NumKeyBoard && d->NumKeyBoard->isVisible())){
        return true;
    } else {
        return false;
    }
}


void InputContext::setFocusObject(QObject *object)
{
    if (object == nullptr){
        return;
    }
    _object = object;
    curWidgetPos = ((QWidget *)object)->mapToGlobal(QPoint(0,0));
    curWidgetRect = ((QWidget *)object)->rect();
    d->keyEventDispatcher.setFocusItem(object);
    if(object->inherits("QLineEdit")){
        showInputPanel();
    }
}
