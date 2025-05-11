#ifndef BLL_H
#define BLL_H

#include <QtCore/qglobal.h>

#if defined(BLL_LIBRARY)
#  define BLLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BLLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BLL_H
