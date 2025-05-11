#include "..\include\precomp\precompile.h"
#include "ShowTestResultDetail.h"
//�����ͷ��ͼ
#include <QHeaderView>
#include <QPushButton>

ShowTestResultDetail::ShowTestResultDetail(QWidget *parent)
	: QTableWidget(parent)
{
	setColumnCount(9);//��������
	setRowCount(10);//��������
	//��ͷ
	setHorizontalHeaderLabels(QStringList() << "���" << "����" << "����"<< "�ܽ����̶�" << "����"<< "רҵ" << "ְ��" << "����" << "ְ��");
	//��ͷ��Ԫ�񱳾�ɫ������
	setStyleSheet(QString("QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold;}"));
	horizontalHeader()->setStretchLastSection(true);//���ñ������洰������
	verticalHeader()->hide();//������ֱ��ͷ
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //����п�����Ӧ
	setSelectionBehavior(QAbstractItemView::SelectRows);//����ѡ������Ϊ��
	setEditTriggers(QAbstractItemView::NoEditTriggers);//���ñ��˫���޸�
}

ShowTestResultDetail::~ShowTestResultDetail()
{
}
