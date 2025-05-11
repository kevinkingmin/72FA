#ifndef MODEL_H
#define MODEL_H

#include <QtCore/qglobal.h>

#if defined(MODEL_LIBRARY)
#  define MODELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODEL_H
