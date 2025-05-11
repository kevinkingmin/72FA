#include "HumaClia2000Data.h"
#include <QFont>
#include <QFontDatabase>

QFont *HumaClia2000Data::getFontAwesome()
{
    static QFont *icofont = nullptr;
    if (icofont == nullptr){
        int fontId = QFontDatabase::addApplicationFont(":/FontAwesome");
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        icofont = new QFont(fontName);
        icofont->setPixelSize(20);
    }
    return icofont;
}
