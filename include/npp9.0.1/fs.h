#ifndef NPP9_0_1_FS_H
#define NPP9_0_1_FS_H

#include "npp_global.h"
#include <QString>

namespace npp090001::fs {

/**
 * @brief ディレクトリの有無を確認し、ない時に再帰的に作成
 * @param filePath 作成するディレクトリ
 */
void NPP_EXPORT mkdir(const QString& filePath);

} // namespace npp090001::fs

#endif // NPP9_0_1_FS_H