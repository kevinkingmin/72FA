#ifndef TESTDATALISTWIDGET_H
#define TESTDATALISTWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QMap>
#include "src/comm/GlobalData.h"

#define PAPERCOUNT 72
#define PAPERSTARPOS 3

class QItemSelection;
class SampleTestModel;
class TestDataListVModel;
class QHBoxLayout;
class CustomLabel1;

namespace Ui {
class TestDataListWidget;
}

class TestDataListWidget : public QWidget
{
    Q_OBJECT
public:   
    using ptrTest=QSharedPointer<SampleTestModel>;
    explicit TestDataListWidget(QWidget *parent = nullptr);
    ~TestDataListWidget();
    void createPapers();
    void setPapersState(QVector<ptrTest> listTestData);

private:
    void initUI();
    ptrTest searchPmByPos(int pos);
private:
    Ui::TestDataListWidget *ui;
    QVector<ptrTest> m_listTest;
    QVector<CustomLabel1 *> _lblPaperVect;
};

#endif // TESTDATALISTWIDGET_H
