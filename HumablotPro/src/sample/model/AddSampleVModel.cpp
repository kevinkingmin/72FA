#include "AddSampleVModel.h"
#include <QColor>
#include "../Include/BLL/baseSet/TestPaperBLL.h"
#include "../Include/Model/baseSet/TestPaperModel.h"
#include "../Include/BLL/baseSet/SystemSetBLL.h"
#include "../Include/Model/baseSet/SystemSetModel.h"
#include <QMessageBox>
#include "src/main/subDialog/MyMessageBox.h"

#include "../../comm/GlobalData.h"
#include "../Include/DAO/Analysis/AnalysisUIDao.h"


#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QPainter>


AddSampleVModel::AddSampleVModel(QWidget *parent) : QAbstractTableModel(parent)
	, _headVect{}
	, _space("       ")
{

	auto dao = AnalysisUIDao::instance();
	bool bResult;

	g_parent = parent;
	HeadStrc pos;
	pos.id = 0;
	pos.paperId = 0;

    QString sz = GlobalData::LoadLanguageInfo("K1048");
	pos.field = sz;//tr(" 位置");
	_headVect.push_back(pos);

	HeadStrc sampleNo;
	sampleNo.paperId = 1;
	sampleNo.id = 1;
    sz = GlobalData::LoadLanguageInfo("K1049");
	sampleNo.field = sz;//tr("样本编号");
	_headVect.push_back(sampleNo);

	HeadStrc cupType;
	cupType.paperId = 2;
	cupType.id = 2;
    sz = GlobalData::LoadLanguageInfo("K1050");
	cupType.field = sz;//tr("试管型号");
	_headVect.push_back(cupType);

	//HeadStrc cupType1;
	//cupType1.paperId = 0;
	//cupType1.field = tr("试管型号ssss");
	//_headVect.push_back(cupType1);
	//5是tsystemset表中第5行的配置信息
	HeadStrc patientName;
	patientName.paperId = 3;
	patientName.id = 3;
    sz = GlobalData::LoadLanguageInfo("K1051");
	patientName.field = sz;//tr("病人姓名");
	_headVect.push_back(patientName);

	HeadStrc sexID;
	sexID.paperId = 4;
	sexID.id = 4;
    sz = GlobalData::LoadLanguageInfo("K1052");
	sexID.field = sz;// tr("性别");
	_headVect.push_back(sexID);

	HeadStrc age;
	age.paperId = 5;
	age.id = 5;
    sz = GlobalData::LoadLanguageInfo("K1053");
	age.field = sz;// tr("年龄");
	_headVect.push_back(age);

	HeadStrc articleNo;
	articleNo.paperId = 6;
	articleNo.id = 6;

    sz = GlobalData::LoadLanguageInfo("K1054");
	articleNo.field = sz;// tr("批号");

	_headVect.push_back(articleNo);
	auto pm = SystemSetBLL().getRowById(5);
	if (!pm.isNull())
	{
		int campany_id = pm->getSaveSet();
		auto vect = TestPaperBLL().getOnUsedRowsByCompanyId(campany_id);
		m_paper_number = vect.count();
		for (auto it : vect)
		{
			HeadStrc paper;
			int headVectCount = _headVect.count();
			//paper.paperId = (headVectCount);
			int paper_id = it->getID();
			paper.paperId = (paper_id);
			paper.id = headVectCount;
			paper.field = it->getPaperName();
			//paper.articleNo = it->getPaperName();
			_headVect.push_back(paper);
		}
	}
}

//void AddSampleVModel::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) {
//
//	if (index.isValid()) {
//		// 自定义绘制控件并设置背景色
//		QPushButton button("Button");
//		button.setGeometry(option.rect);
//		button.setStyleSheet("background-color: lightblue;"); // 设置控件背景色
//		QPixmap pixmap(button.size());
//		button.render(&pixmap);
//		painter->drawPixmap(option.rect, pixmap, pixmap.rect());
//	}
//}


QVariant AddSampleVModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (Qt::DisplayRole != role)
		return QVariant();

	if (section >= _headVect.size())
		return QVariant();

	if (Qt::Horizontal == orientation)
		return _headVect.at(section).field;
	else
		return QString("%1").arg(section);
}

int AddSampleVModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return _vect.count();
}

int AddSampleVModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return _headVect.size();
}

QVariant AddSampleVModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	int row = index.row();
	int column = index.column();


	//if (role == Qt::CheckStateRole && index.column() == 0) {
	//	return checkboxes_[index.row()] ? Qt::Checked : Qt::Unchecked;
	//}
	//return AddSampleVModel::data(index, role);
	           
	//if (role == Qt::BackgroundRole && index.row() == 3 && index.column() == 3) {
	//	return QColor(255, 0, 0); // 返回透明的背景色
	//}


	//if (role == Qt::BackgroundRole ) {
	//	// 返回自定义的背景数据
	//	// 例如：return QBrush(QColor(255, 0, 0)); // 红色背景
	//	return QColor(255, 0, 0); // 
	//}

	//if (role == Qt::BackgroundRole && index.row() == 1 && index.column() == 1) {
	//	return QColor(255, 0, 0, 200); // 返回透明的背景色
	//}

	if (Qt::TextAlignmentRole == role)
	{
		//if (column > 2)
		//return  QVariant(Qt::AlignHCenter | Qt::AlignBottom);
		//return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
		return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
	}
	else if (Qt::TextColorRole == role)
	{
		//if (column > 2)
		//	return QColor(0, 0, 255);
	}
	if (_vect.count() <= row)
		return QVariant();
    auto m = _vect.at(row);

	if (Qt::DisplayRole == role || Qt::EditRole == role)
	{
		//if (_vect.count() > row && column < _headVect.count() - 1)
		if (_vect.count() > row && column < _headVect.count())
		{
			if (column == 0)
                return m.samplePos;
			else if (column == 1)
                return m.sampleNo;
			else if (column == 2)
                return m.cupTypeText;
			else if (column == 3)
				return m.patientName;
			else if (column == 4)
			{
				return m.sexIDText;
				// 获取本行性别数据
				//int gender = m.sexID;
				// 如果性别为 true，则返回字符串 "男"，否则返回 "女"
				//return gender==1 ? tr("男") : tr("女");
				//return m.sexID;
			}
			else if (column == 5)
				return m.age;
			else if (column == 6)
				return m.articleNo;
			else if (column > _headVect.count() - m_paper_number-1)
			{
				auto map = m.paperCheckedCountMap;
				if (map.keys().contains(column))
				{
					auto count = std::get<1>(map[column]);
					if (count > 1)
						return "   " + _space + QString::number(count);
				}
				return _space;
			}
		}
	}
	else if (role == Qt::CheckStateRole)
	{
		if (column > _headVect.count() - m_paper_number-1)
		{
			auto map = m.paperCheckedCountMap;
			if (map.keys().contains(column))
				return std::get<0>(map[column]) ? Qt::Checked : Qt::Unchecked;
		}
		//////////////////////////////
		//if (index.column() == 0) {
		//	return m_data_check[index.row()][index.column()] ? QVariant(true) : QVariant(false);
		//}
		//else {
		//	return QVariant();
		//}
		///////////////////////////////////
	}
	return QVariant();
}

Qt::ItemFlags AddSampleVModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return QAbstractItemModel::flags(index);

	Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

	if (index.column() == 0 || index.column() == _headVect.count())
		return QAbstractItemModel::flags(index);
	else if (index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 4 || index.column() == 5 || index.column() == 6)
		return  defaultFlags | QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	else
		return  QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;

	//return defaultFlags | Qt::ItemIsSelectable;
	//Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	//if (index.column() == 0) {
	//	flags |= Qt::ItemIsUserCheckable;
	//}
	//else {
	//	flags |= Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
	//}

	//return flags;

}

bool AddSampleVModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	int row = index.row();
	int column = index.column();
	QString sample_no = "";
	auto regExp = QRegExp("[a-zA-Z0-9]*");

	if (!index.isValid())
	{
		return false;
	}

	//if (role == Qt::CheckStateRole && index.column() == 0) {
	//	checkboxes_[index.row()] = value == Qt::Checked;
	//	emit dataChanged(index, index);
	//	return true;
	//}
	//return AddSampleVModel::setData(index, value, role);






	if (Qt::EditRole == role)
	{
		switch (column)
		{
		case 1:
			sample_no = value.toString();
			if (sample_no.length() > 20)
			{
                MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1355"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"),"");
				_vect[row].sampleNo = "";
			}
			else
			{
				if (regExp.exactMatch(sample_no)) {
					// 符合条件
					_vect[row].sampleNo = value.toString();
				}
				else {
                    MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1356"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"),"");
					// 不符合条件
				}
				//_vect[row].sampleNo = value.toString();
			}
			break;
		case 2:
		{
			auto arr = value.toString().split(',');
			_vect[row].cupTypeText = arr[0];
			_vect[row].cupType = arr[1].toInt();

			//_vect[row].articleNo = "2ssddd";// value.toString();
			//_vect[row].articleNo = arr[2];
			break;
		}
        case 3:
		{
			if (value.toString().length() > 20)
			{
                MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1357"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"),"");
				_vect[row].patientName = "";
			}
			else
			{
				_vect[row].patientName = value.toString(); //"3ssddd";// value.toString();
			}
			break;
		}

		case 4:
		{
			auto arr1 = value.toString().split(',');
			_vect[row].sexIDText = arr1[0];
			_vect[row].sexID = arr1[1].toInt();

			//if (value.toInt() > 1)
			//{
            //	QMessageBox::information(NULL, GlobalData::LoadLanguageInfo("K1180"), "性别不能为大于1", "确定");
			//	_vect[row].sexID = 1;// "4ssddd";// value.toString();
			//}
			//else if (value.toInt() < 0)
			//{
            //	QMessageBox::information(NULL, GlobalData::LoadLanguageInfo("K1180"), "性别不能为负数", "确定");
			//	_vect[row].sexID = 0;// "4ssddd";// value.toString();
			//}
			//else
			//{
			//	_vect[row].sexID = value.toInt();// "4ssddd";// value.toString();
			//}

			//// 将字符串转换为布尔值，并将其设置为本行性别数据

			//_vect[index.row()].sexID = value.toString().compare(tr("男"))?1:0;
			//return true;
			break;
		}
		case 5:
			if (value.toInt() < 0)
			{
                MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1358"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"),"");
				_vect[row].age = 0;
			}
			else if (value.toInt() > 150)
			{
                //QMessageBox::warning(AddSampleVModel.t, GlobalData::LoadLanguageInfo("K1180"), "数据上传LIS完成！", "确定");
                MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1359"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"),"");
				_vect[row].age = 150;
			}
			else
			{
				_vect[row].age = value.toInt();// "5ssddd";// value.toString();
			}

			break;
		case 6:
			if (value.toString().length() > 15)
			{
                MyMessageBox::information(g_parent, GlobalData::LoadLanguageInfo("K1180"), GlobalData::LoadLanguageInfo("K1360"), MyMessageBox::Ok, GlobalData::LoadLanguageInfo("K1181"),"");
				_vect[row].articleNo = "";
			}
			else
			{
				_vect[row].articleNo = value.toString();
			}

			break;

		default:
			break;
		}
		emit dataChanged(index, index);

		return true;
	}

	/////////////////////////////////////////
	//if (role == Qt::EditRole && index.column() > 6) {
	//	m_data_check[index.row()][index.column()] = value.toBool();
	//	return true;
	//}
	///////////////////////////////////////////////////////////


	//if (Qt::EditRole == role)
	//{
	//	switch (column)
	//	{
	//	case 1:
	//		_vect[row].sampleNo = value.toString();
	//		break;
	//	case 2:
	//	{
	//		auto arr = value.toString().split(',');
	//		_vect[row].cupTypeText = arr[0];
	//		_vect[row].cupType = arr[1].toInt();
	//		//_vect[row].articleNo = "2ssddd";// value.toString();
	//		//_vect[row].articleNo = arr[2];
	//		break;
	//	}
	//	case 3:
	//		_vect[row].patientName = value.toString(); //"3ssddd";// value.toString();
	//		break;
	//	case 4:
	//		_vect[row].sexID = value.toInt();// "4ssddd";// value.toString();
	//		break;
	//	case 5:
	//		_vect[row].age = value.toInt();// "5ssddd";// value.toString();
	//		break;
	//	case 6:
	//		_vect[row].articleNo = value.toString();
	//		break;

	//	default:
	//		break;
	//	}
	//	emit dataChanged(index, index);
	//	return true;
	//}

    else if (role == Qt::CheckStateRole)
	{
        if (column > _headVect.count() - m_paper_number-1)
		{
			auto &map = _vect[row].paperCheckedCountMap;
			if (map.keys().contains(column))
			{
				auto &tp = map[column];
				int num = std::get<1>(tp);
				if (std::get<0>(tp))
				{
					//是否要取消选择
					//int ret = QMessageBox::information(nullptr, "提示信息", "确定要取消项目选择？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    int ret = MyMessageBox::question(g_parent, GlobalData::LoadLanguageInfo("K1088"), GlobalData::LoadLanguageInfo("K1361"), MyMessageBox::Yes | MyMessageBox::No, GlobalData::LoadLanguageInfo("K1181"), GlobalData::LoadLanguageInfo("K1134"));
					if (ret== MyMessageBox::Yes)
					{
						std::get<0>(tp) = value.toBool();
						//std::get<1>(tp) = num;
					}
				}
				else
				{
					std::get<0>(tp) = value.toBool();
					//std::get<1>(tp) = num;
				}

			}
			emit rowSeletedByChecked(row, column);
		}
		emit dataChanged(index, index);
		return true;
	}
	return false;
}

void AddSampleVModel::updateData()
{
	beginResetModel();
	endResetModel();
	QVector<dataStrc> vect;
	_vect.swap(vect);
    for (int i = 1; i <= PAPERCOUNT; i++)
	{
		dataStrc dt;
		dt.samplePos = i;
		for (int jj = _headVect.count()- m_paper_number; jj < _headVect.count(); jj++)
		{
			std::tuple tp(false, 1);
			dt.paperCheckedCountMap.insert(jj, tp);
		}
        //for (int j = PAPERSTARPOS; j < _headVect.count() - 4; j++)
		//{
		//	std::tuple tp(false, 1);
		//	dt.paperCheckedCountMap.insert(j, tp);
		//}
		_vect.push_back(dt);
	}
	this->layoutChanged();//.layoutChanged.emit();
}

QVector<AddSampleVModel::HeadStrc> &AddSampleVModel::getHeadVect()
{
	return _headVect;
}

QVector<AddSampleVModel::dataStrc> &AddSampleVModel::getVect()
{
	return _vect;
}

