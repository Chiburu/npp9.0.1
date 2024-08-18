#ifndef NPP9_0_1_PATH_H
#define NPP9_0_1_PATH_H

#include "npp_global.h"
#include <QString>
#include <QList>

namespace npp090001::path {

/**
 * @brief パスの書式を統一する。
 * バックスラッシュ区切りをスラッシュ区切りにする。
 * @tparam Text 文字列型(replaceメソッドを有するクラス)
 * @param path パス
 * @return Text 統一された書式のパス
 */
template <class Text>
Text unify(const Text& path) {
  Text copy(path);
  copy.replace("\\", "/");
  return copy;
}

/**
 * @brief パスをつなぎ合わせる。
 * @tparam Text 文字列型
 * @param list パスリスト
 * @return QString スラッシュでつなぎ合わせたパス
 */
template <class Text>
Text join(const QList<Text> &list) {
  return list.join("/");
}

/**
 * @brief パスからファイル名を取得する。
 * @param path パス
 * @return QString ファイル名のみ
 */
QString NPP_EXPORT getFileName(const QString &path);

} // namespace npp090001::path

#endif // NPP9_0_1_PATH_H