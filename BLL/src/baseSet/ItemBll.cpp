#include "ItemBll.h"


ItemBll::ItemBll()
{
}

QVector<ItemModel> ItemBll::getRowsByPaperId(int paperId)
{
    return ItemDao::instance()->selectItems(paperId);
}

