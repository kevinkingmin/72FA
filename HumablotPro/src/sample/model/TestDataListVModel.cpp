#include "TestDataListVModel.h"
#include <QDateTime>
#include <QColor>
#include <QFont>
#include "src/comm/GlobalData.h"
#include "../Include/Model/sample/SampleTestModel.h"
#include "../Include/BLL/baseSet/TestPaperBLL.h"
#include "../Include/Model/baseSet/TestPaperModel.h"

#include "../../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

TestDataListVModel::TestDataListVModel(QObject *parent)
    : QAbstractTableModel(parent)
{
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");
    //_headerList<<tr("sampleId")<<tr("膜条预订位")<<tr("样本编号")<<tr("检测")<<tr("样本位")<<tr("批号") << tr("备注");
	//_headerList << tr("sampleId") << tr("膜条预订位") << tr("样本编号") << tr("检测") << tr("样本位") << tr("批号") ;

	QString sz1 = GlobalData::LoadLanguageInfo(g_language_type, "K1065");
	QString sz2 = GlobalData::LoadLanguageInfo(g_language_type, "K1066");
	QString sz3 = GlobalData::LoadLanguageInfo(g_language_type, "K1067");
	QString sz4 = GlobalData::LoadLanguageInfo(g_language_type, "K1068");
	QString sz5 = GlobalData::LoadLanguageInfo(g_language_type, "K1069");
	_headerList << tr("sampleId") << sz1 << sz2 << sz3 << sz4 << sz5;
}

QVariant TestDataListVModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (Qt::DisplayRole != role)
        return QVariant();
    if (section >= _headerList.size())
        return QVariant();
    if (Qt::Horizontal == orientation)
        return _headerList.at(section);
    else
        return QString("%1").arg(section);
}

int TestDataListVModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _vect.count();
}

int TestDataListVModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _headerList.size();
}

QVariant TestDataListVModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row    = index.row();
    int column = index.column();
    ptrTest pm;
    if(_vect.count() > row)
        pm=_vect.at(row);
    else
        return QVariant();
    if(Qt::TextAlignmentRole == role)
    {
       return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if(role==Qt::BackgroundColorRole)
    {
        if(column == 1)
        {
            //if(pm->getSlotPos()<=24)
            //{
            //    return QColor(FIRSTPAPERRACK);
            //}
            //else if(pm->getSlotPos()<=48)
            //{
            //    return QColor(SECONDPAPERRACK);
            //}
            //else if(pm->getSlotPos()<=72)
            //{
            //    return QColor(THIRDPAPERRACK);
            //}

			if (pm->getSlotPos() <= 24)
			{
				return QColor("#F0F0F0");
			}
			else if (pm->getSlotPos() <= 48)
			{
				return QColor("#F0F0F0");
			}
			else if (pm->getSlotPos() <= 72)
			{
				return QColor("#F0F0F0");
			}
        }
    }
    else if(role==Qt::FontRole)
    {
        if(column==1)
        {
            QFont font;
            font.setBold(true);
            font.setPixelSize(19);
            return font;
        }
    }
    else if (Qt::DisplayRole==role || Qt::EditRole==role)
    {
        switch (column)
        {
        case 0:
            return pm->getSampleId();
			break;
        case 1:
            return pm->getSlotPos();
			break;
        case 2:
            return pm->getRemark();
			break;
        case 3:
        {
			auto paper = TestPaperBLL().getRowById(pm->getPaperId());
            if(paper.isNull())
                return "";
            return paper->getPaperName();
			break;
        }
        case 4:
		{
			//auto paper1 = TestPaperBLL().getRowById(pm->getPaperId());
			//if (paper1.isNull())
			//	return "";
			return pm->getSamplePos();
			break;
		}
   //     case 5:
			//return pm->getArticleNo();
   //         //return  "";
			//break;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

Qt::ItemFlags TestDataListVModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return  QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

void TestDataListVModel::updatePage(QVector<ptrTest> vect)
{
    beginResetModel();
    _vect.swap(vect);
    endResetModel();
}
