#ifndef NPP9_0_1_ENV_H
#define NPP9_0_1_ENV_H

#include "npp_global.h"
#include <QByteArray>
#include <functional>

namespace npp090001::env {

/**
 * @brief notes.ini から文字列変数値を取得
 * @param key 変数名
 * @param fn デフォルト値を取得する関数
 * @return QByteArray 文字列変数値
 */
QByteArray NPP_EXPORT getString(
  const char *key,
  std::function<QByteArray()> fn
);

/**
 * @brief notes.ini から文字列変数値を取得
 * @param key 変数名
 * @param fn デフォルト値を取得する関数
 * @return QByteArray 文字列変数値
 */
QByteArray NPP_EXPORT getString(
  const QByteArray& key,
  std::function<QByteArray()> fn
);

/**
 * @brief notes.ini から文字列変数値を取得
 * @param key 変数名
 * @param defaultValue デフォルト値
 * @return QByteArray 文字列変数値
 */
QByteArray NPP_EXPORT getString(
  const char *key,
  const QByteArray& defaultValue
);

/**
 * @brief notes.ini から文字列変数値を取得
 * @param key 変数名
 * @param defaultValue デフォルト値
 * @return QByteArray 文字列変数値
 */
QByteArray NPP_EXPORT getString(
  const QByteArray& key,
  const QByteArray& defaultValue
);

/**
 * @brief Notesクライアント/Dominoサーバのデータディレクトリを取得
 * @return QByteArray データディレクトリパス
 */
QByteArray NPP_EXPORT getDataDirectory();

} // namespace npp090001::env

#endif // NPP9_0_1_ENV_H