#ifndef THEME_GLOBAL_H
#define THEME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(THEME_LIBRARY)
#  define THEMESHARED_EXPORT Q_DECL_EXPORT
#else
#  define THEMESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // THEME_GLOBAL_H
