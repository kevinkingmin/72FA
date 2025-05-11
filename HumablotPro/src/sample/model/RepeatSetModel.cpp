#include "RepeatSetModel.h"
#include <QColor>
#include "../Include/Utilities/log.h"
#include <QMessageBox>
#include "src/main/subDialog/MyMessageBox.h"
#include "src/comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"

QVector<std::tuple<int, int>> RepeatSetModel::m_posCountVect{};
RepeatSetModel::RepeatSetModel(QWidget *parent)
    : QAbstractTableModel(parent)
    ,m_data(nullptr)
{
	auto dao = AnalysisUIDao::instance();
	bool bResult;
	g_language_type = dao->SelectTargetValueDes(&bResult, "20005");

		_headerList << GlobalData::LoadLanguageInfo(g_language_type, "K1180") << GlobalData::LoadLanguageInfo(g_language_type, "K1131") << GlobalData::LoadLanguageInfo(g_language_type, "K1551");
    //_headerList<<tr("pos")<<tr("项目名称")<<tr("测试次数");
    _headVect=AddSampleVModel().getHeadVect();
	g_parent = parent;
}

QVariant RepeatSetModel::headerData(int section, Qt::Orientation orientation, int role) const
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

int RepeatSetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || m_data==nullptr)
        return 0;
	QVector<std::tuple<int, int>> vect;
    int count=0;
	auto &map = m_data->paperCheckedCountMap;
	for (auto it = map.begin(); it != map.end(); it++)
	{
		bool isChecked = std::get<0>(it.value());
		if (isChecked)
		{
			std::tuple<int, int>tp(it.key(), std::get<1>(it.value()));
			vect.push_back(tp);
			count++;
		}
	}
	m_posCountVect.swap(vect);
    return count;
}

int RepeatSetModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return _headerList.size();
}

QVariant RepeatSetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_data==nullptr)
        return QVariant();

    int row    = index.row();
    int column = index.column();

    if(Qt::TextAlignmentRole == role)
    {
       QVariant value(Qt::AlignLeft | Qt::AlignVCenter);
       return value;
    }

    if(role==Qt::BackgroundColorRole)
    {
        if(column==2)
            return QVariant(QColor(255,192,203));
    }

    if (Qt::DisplayRole==role || Qt::EditRole==role)
    {
        if (m_posCountVect.count() > row)
        {
			auto posCount = m_posCountVect.at(row);
			auto pos = std::get<0>(posCount);
			auto count= std::get<1>(posCount);
            switch (column)
            {
            case 0:
                return pos;
            case 1:
                return _headVect.at(pos).field;
            case 2:
                return count;
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags RepeatSetModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    if(index.column()==2)
    {
        return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
    }
    return  QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

bool RepeatSetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || m_data == nullptr)
    {
        return false;
    }
    if(Qt::EditRole == role)
    {
        int row = index.row();
        int column = index.column();       
        switch (column)
        {
        case 2:
        {
            auto &map = m_data->paperCheckedCountMap;
			auto pos = std::get<0>(m_posCountVect.at(row));
            auto keys = map.keys();

            int v=0;
            if(keys.contains(pos))
            {
                auto &tp=map[pos];
                v=value.toInt();
				if (v <= 0)
				{
					MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1180"), GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1362"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo(GlobalData::getLanguageType(), "K1181"), "");
                    goto NEXT;
				}
                std::get<1>(tp)=v;
            }
            else
            {
                eLog("没有找到此项目,pos:{}", pos);
                goto NEXT;
            }
            break;
        }
        default:
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
NEXT:
    return false;
}

void RepeatSetModel::updatePage(dataStrc *data)
{
    beginResetModel();
    m_data = data;
    endResetModel();
}


