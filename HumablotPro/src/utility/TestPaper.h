#pragma once

#include <QDialog>
#include "ui_TestPaper.h"
#include <QMap>
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/Model/baseSet/ItemModel.h"

class TestPaper : public QDialog
{
    struct Item_Control
    {
        QLabel	  *label;
        QLineEdit *lineEdit_Name;
        QCheckBox *checkBox;
        QComboBox *combo_item_type;
        QLineEdit *lineEdit_Position;
        QComboBox *combo_box_rule;
        QComboBox *cmbCurve;
        Item_Control()
            :label(nullptr)
            ,lineEdit_Name(nullptr)
            ,checkBox(nullptr)
            ,lineEdit_Position(nullptr)
            ,combo_box_rule(nullptr)
            ,cmbCurve(nullptr)
        {}

        void setCtlVisible(const bool visible)
        {
            label->setVisible(visible);
            lineEdit_Name->setVisible(visible);
            checkBox->setVisible(visible);
            combo_item_type->setVisible(visible);
            lineEdit_Position->setVisible(visible);
            combo_box_rule->setVisible(visible);
            cmbCurve->setVisible(visible);
        }
    };

    // 分段膜条
    struct BlockControl
    {
        QLabel	  *label;
        QComboBox *cmbItemCount;
        BlockControl()
            :label(nullptr)
            ,cmbItemCount(nullptr)
        {}
        void setCtlVisible(const bool visible)
        {
            label->setVisible(visible);
            cmbItemCount->setVisible(visible);
        }
    };

    //分段膜条
    struct BlockItemCtl
    {        
        QComboBox *cmbItemType;
        QLineEdit *itemNameEdit;
        QCheckBox *checkBox;
        int       blockNo;
        QComboBox *cmbRuleBox;
        QComboBox *cmbCurveBox;
        bool      isNew;
        int       serialNo;
        BlockItemCtl()
            :cmbItemType(nullptr)
            ,itemNameEdit(nullptr)
            ,blockNo(0)
            ,cmbRuleBox(nullptr)
            ,cmbCurveBox(nullptr)
            ,isNew(true)
            ,serialNo(0)
        {}
    };

    struct BaseGridItemCtl
    {
        QVector<QLabel*>gridHead1;
        QVector<QLabel*>gridHead2;
        QTableWidget  *table;
        BaseGridItemCtl():
            gridHead1{}
            ,gridHead2{}
            ,table(nullptr)
        {}
        virtual ~BaseGridItemCtl(){}
        void setHeadShow(const bool isShowTable)
        {
            if(table!=nullptr)
            {
                if(isShowTable)
                    table->setVisible(true);
                else
                    table->setVisible(false);
            }

            for (int i = 0; i < gridHead1.count(); i++)
            {
                gridHead1.at(i)->setVisible(true);
                gridHead2.at(i)->setVisible(true);
            }
        }

        void setHeadHide()
        {
            for (int i = 0; i < gridHead1.count(); i++)
            {
                gridHead1.at(i)->setVisible(false);
                gridHead2.at(i)->setVisible(false);
            }
        }
        virtual void showAllCtl(){}
        virtual void showCtlByCount(const int count){Q_UNUSED(count)}
    };

    struct GridLayItemCtl:public BaseGridItemCtl
    {
        QMap<int,Item_Control> itemCtlMap;
        GridLayItemCtl()
            :itemCtlMap{}
        {}

        void showAllCtl()
        {
            setHeadShow(false);
            for (auto &ctl : itemCtlMap)
            {
                if (ctl.label == nullptr)
                    continue;
                ctl.setCtlVisible(true);
            }
        }

        void showCtlByCount(const int count)
        {
            int i=0;
            for(auto ctl:itemCtlMap)
            {
                i++;
                if(count>=i)
                    ctl.setCtlVisible(true);
                else
                    ctl.setCtlVisible(false);
            }
            setHeadShow(false);
            if(count<=15)
            {
                for(auto &lbl:gridHead2)
                    lbl->setVisible(false);
            }
        }
        void hiddeAll()
        {
            setHeadHide();
            for(auto ctl:itemCtlMap)
                ctl.setCtlVisible(false);
        }
    };

    struct GridLayBlockCtl:public BaseGridItemCtl
    {
        QMap<int,BlockControl> blockCtlMap;
        GridLayBlockCtl()
            :blockCtlMap{}
        {}
        void showAllCtl()
        {
            setHeadShow(true);
            for (auto &ctl : blockCtlMap)
            {
                if (ctl.label == nullptr)
                    continue;
                ctl.setCtlVisible(true);
            }
        }

        void showCtlByCount(const int count)
        {
            int i=0;
            for(auto ctl:blockCtlMap)
            {
                i++;
                if(count>=i)
                    ctl.setCtlVisible(true);
                else
                    ctl.setCtlVisible(false);
            }
            setHeadShow(true);
            if(count<=15)
            {
                for(auto &lbl:gridHead2)
                    lbl->setVisible(false);
            }
        }

        void hiddeAll()
        {
            setHeadHide();
            for(auto ctl:blockCtlMap)
                ctl.setCtlVisible(false);
        }
    };

    struct TestPaper_Item
    {
        bool	isNullArea;
        int     serialNo;
        int     itemType;
        QString	strItemName;
        int     judgerule;
        double  position;
        int     curve;
        TestPaper_Item()
            :isNullArea(false)
            ,serialNo(0)
            ,itemType(0)
            ,strItemName("")
            ,judgerule(0)
            ,position(0)
            ,curve(0)
        {}
    };

    // 分段膜条块设置
    struct BlockData
    {
        int     serialNo;
        int     itemCount;
        BlockData()
            :serialNo(0)
            ,itemCount(0)
        {}
    };

    // 分段膜条项目设置
    struct BlockItemData
    {
        int     serialNo;
        int itemType;
        QString	strItemName;
        bool ignore; // 是否忽略此项目
        int     blockNo;
        int     judgerule;
        int curve;
        BlockItemData()
            :itemType(0)
            ,strItemName("")
            ,blockNo(0)
            ,judgerule(0)
            ,curve(0)
        {}
    };

    struct BlockAndItemData
    {
        BlockData blockData;
        QVector<BlockItemData> itemDatas;
        BlockAndItemData()
            :blockData()
            ,itemDatas{}
        {}
    };

    struct ComboxData
    {
        QString  cmbText;
        QString  cmbData;
        ComboxData()
            :cmbText("")
            ,cmbData("")
        {}
        ComboxData(const QString &text,const QString &data)
            :cmbText(text)
            ,cmbData(data)
        {}
    };
    Q_OBJECT
public:
    TestPaper(QWidget *parent = Q_NULLPTR);
    virtual~TestPaper()override;    
    void Set_UI(const QString &paperId,const QString &companyId, bool isModify);
protected:
//    void closeEvent(QCloseEvent *event) override;
private:
    void initUI();
    bool Save_TestPaper_Items();
    bool Save_TestPaper_Parameters();
    void getAllItemControl();
    void getUIItemData();
    void getUIBlockAndItemData();
    void initComboBox();
    inline void setComBoBoxData(QComboBox *cmb,const QVector<ComboxData> &datas);
    void uiCtlSet(const int itemCount=-1);
    inline void tbSegmentAddData(const int oldRow);
private slots:
    void on_pushButton_Set_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_Cancel_clicked();
    void on_cmbPaperType_currentIndexChanged(int index);
    void color_slots_func();
    void slotCmbRuleDataSet(int index);
    void slotCmbCurveDataSet(int index);
    void slotRightCmbRuleDataSet(int index);
    void slotRightCurveDataSet(int index);
    void slotCreatDetailRows(const QString &data);
    void slotCmbCompanyTextChanged(const QString &text);
private:
    Ui::TestPaper                   *ui;
    QString                         m_strMachineUID;
    GridLayItemCtl                  m_gridItemCtl;
    QMap<int,TestPaper_Item>        m_itemDataMap;
    GridLayBlockCtl                 m_gridBlockCtl;
    QMap<int,BlockAndItemData>      m_blockAndItemDataMap;
    QMap<int,QVector<BlockItemCtl>> m_blockItemCtlMap;
    QVector<ComboxData>             m_ruleCmbDatas;//规则下拉框数据
    QVector<ComboxData>             m_curveCmbDatas;//曲线下拉框数据
    QVector<ComboxData>             m_itemTypeCmbDatas;//项目类型下拉数据
    bool                            _isNeedUpdate;
    QString                         _paperId;
    bool                            m_bModify;
    QString                         m_Company_ID;
    TestPaperModel                  _testPaperModel;
    QVector<ItemModel>              _itemModelVect;
};
