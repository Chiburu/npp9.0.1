#ifndef NPP9_0_1_OS_H
#define NPP9_0_1_OS_H

#include "npp_global.h"
#include <QString>

namespace npp090001::os {

/**
 * @brief 実行中のプロセスのファイル名を取得
 * @return QString 実行中のプロセスのファイル名
 */
QString NPP_EXPORT getProcessPath();

} // namespace npp090001::os

#endif // NPP9_0_1_OS_H