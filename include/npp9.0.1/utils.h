#ifndef NPP9_0_1_UTILS_H
#define NPP9_0_1_UTILS_H

#include "npp_global.h"
#include <QString>
#include <functional>
#include <optional>

namespace npp090001 {

/**
 * @brief 二分木関数
 * @tparam T 戻り値型
 * @param conditions 条件判定関数
 * @param fnThen 条件がtrue時に実行する関数
 * @param fnElse 条件がelse時に実行する関数
 * @return T 戻り値
 */
template <typename T>
T tree(
  std::function<bool()> conditions,
  std::function<T()> fnThen,
  std::function<T()> fnElse
) {
  return conditions() ? fnThen() : fnElse();
}

/**
 * @brief オプショナル版二分木関数
 * @tparam T 戻り値型
 * @param conditions 条件判定関数
 * @param fnThen 条件がtrue時に実行する関数
 * @return T fnThenの戻り値
 * @return std::nullopt 条件がelse判定
 */
template <typename T>
std::optional<T> opt_tree(
  std::function<bool()> conditions,
  std::function<T()> fnThen
) {
  if (conditions()) {
    return fnThen();
  }
  return std::nullopt;
}

/**
 * @brief 二分木関数
 * @param conditions 条件判定関数
 * @param fnThen 条件がtrue時に実行する関数
 * @param fnElse 条件がelse時に実行する関数
 */
inline void tree(
  std::function<bool()> conditions,
  std::function<void()> fnThen,
  std::function<void()> fnElse
) {
  if (conditions()) {
    fnThen();
  } else {
    fnElse();
  }
}

/**
 * @brief 二分木関数
 * else時は何もしない
 * @param conditions 条件判定関数
 * @param fnThen 条件がtrue時に実行する関数
 */
inline void tree(
  std::function<bool()> conditions,
  std::function<void()> fnThen
) {
  if (conditions()) {
    fnThen();
  }
}

/**
 * @brief 大文字/小文字区別なしで文字列を比較する。
 * @param lhs 左辺値
 * @param rhs 右辺値
 * @return true 同値
 * @return false 異値
 */
inline bool weakEq(const QString& lhs, const QString& rhs) {
  return lhs.compare(rhs, Qt::CaseInsensitive) == 0;
}

/**
 * @brief リスト要素をすべてtrueと判定したらtrueを返す
 * @tparam T 要素の型
 * @param list 元の要素リスト
 * @param fn 要素を判定する関数
 * @return true 要素すべてがtrue
 * @return false 要素のいずれかがfalse
 */
template <typename T>
bool every(const QList<T>& list, std::function<bool(const T&)> fn) {
  foreach (T item, list) {
    if (!fn(item)) return false;
  }
  return true;
}

/**
 * @brief リスト要素のいずれかをtrueと判定したらtrueを返す
 * @tparam T 要素の型
 * @param list 元の要素リスト
 * @param fn 要素を判定する関数
 * @return true 要素のいずれかががtrue
 * @return false 要素すべてがfalse
 */
template <typename T>
bool some(const QList<T>& list, std::function<bool(const T&)> fn) {
  foreach (T item, list) {
    if (fn(item)) return true;
  }
  return false;
}

} // namespace npp090001

#endif // NPP9_0_1_UTILS_H