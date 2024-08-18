#ifndef NPP9_0_1_NPP_GLOBAL_H
#define NPP9_0_1_NPP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NPP9_0_1_LIBRARY)
#define NPP_EXPORT Q_DECL_EXPORT
#else
#define NPP_EXPORT Q_DECL_IMPORT
#endif

// Windows 32bit 版のみ構造体のアラインメントを1バイトにする
#if defined(W32) && (!defined(W64) || !defined(UNIX))
#define PUSH_PACK1 __pragma(pack(push, 1))
#define POP_PACK __pragma(pack(pop))
#else
#define PUSH_PACK1
#define POP_PACK
#endif

#endif // NPP9_0_1_NPP_GLOBAL_H
