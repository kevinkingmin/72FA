
#include "freezeTableView.h"
#include <QScrollBar>
#include <QHeaderView>
#include <QMouseEvent>
#include <QDebug>
#include "customerTableView.h"

FreezeTableView::FreezeTableView(QAbstractItemModel * model)
{
    setModel(model);
    frozenTableView = new CustomerTableView(this);
    frozenTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    frozenTableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    init();

    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &FreezeTableView::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &FreezeTableView::updateSectionHeight);

    connect(frozenTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            frozenTableView->verticalScrollBar(), &QAbstractSlider::setValue);

    connect(frozenTableView,&QTableView::clicked,this,&QTableView::clicked);
}

FreezeTableView::~FreezeTableView()
{
    delete frozenTableView;
}

void FreezeTableView::init()
{
    frozenTableView->setModel(model());
    frozenTableView->setFocusPolicy(Qt::NoFocus);
    frozenTableView->verticalHeader()->hide();
    frozenTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    viewport()->stackUnder(frozenTableView);

    frozenTableView->setStyleSheet("QTableView { border: none;}");
    frozenTableView->setSelectionModel(selectionModel());
    for (int col = 2; col < model()->columnCount(); ++col)
        frozenTableView->setColumnHidden(col, true);

    frozenTableView->setColumnWidth(0, columnWidth(0) );
    frozenTableView->setColumnWidth(1, columnWidth(1) );

    frozenTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    frozenTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    frozenTableView->show();

    updateFrozenTableGeometry();

    setHorizontalScrollMode(ScrollPerItem);
    setVerticalScrollMode(ScrollPerItem);
    frozenTableView->setVerticalScrollMode(ScrollPerItem);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void FreezeTableView::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
    frozenTableView->setColumnWidth(logicalIndex, newSize);
    updateFrozenTableGeometry();
}

void FreezeTableView::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
    frozenTableView->setRowHeight(logicalIndex, newSize);
    updateFrozenTableGeometry();
}

void FreezeTableView::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}

QModelIndex FreezeTableView::moveCursor(CursorAction cursorAction,
                                        Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (cursorAction == MoveLeft && current.column() > 0
            && visualRect(current).topLeft().x() < frozenTableView->columnWidth(0) ){
        const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                - frozenTableView->columnWidth(0);
        horizontalScrollBar()->setValue(newValue);
    }
    return current;
}

void FreezeTableView::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}

QTableView *FreezeTableView::getFrozenTableView() const
{
    return frozenTableView;
}

void FreezeTableView::updateFrozenTableGeometry()
{
    frozenTableView->setGeometry(verticalHeader()->width() + frameWidth(),
                                 frameWidth(), columnWidth(0)+columnWidth(1),
                                 viewport()->height()+horizontalHeader()->height());
}

void FreezeTableView::mousePressEvent(QMouseEvent *event)
{
    int xPos = event->x();
    int yPos = event->y();
    QModelIndex idx = indexAt(QPoint(xPos, yPos));
    if(!idx.isValid( ))
    {
        emit signalBlankArea(event);
    }
	else
	{
        emit signalDataArea(event);
        if(event->button()==Qt::RightButton)
        {
            return;
        }
    }
    QTableView::mousePressEvent(event);
}
