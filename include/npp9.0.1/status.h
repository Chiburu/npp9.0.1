#ifndef NPP9_0_1_STATUS_H
#define NPP9_0_1_STATUS_H

#include "npp_global.h"
#include <QByteArray>
#include <exception>

PUSH_PACK1
#include <global.h>
POP_PACK

namespace npp090001 {

/**
 * @brief ステータスクラス
 * ステータス値は以下の4つのパートからなる。
 * 0x8000: 表示済みフラグ
 * 0x4000: リモートフラグ
 * 0x3f00: パッケージ
 * 0x00ff: エラー番号
 */
class NPP_EXPORT Status
  : public std::exception
{
  STATUS status_; ///< ステータス値

public:
  /**
   * @brief デフォルトコンストラクタ
   */
  Status();

  /**
   * @brief コンストラクタ
   * @param status ステータス値
   */
  Status(STATUS status);

  /**
   * @brief すべてを含むステータス値を返す
   * @return STATUS ステータス値
   */
  STATUS status() const {
    return status_;
  }

  /**
   * @brief フラグ2つを除いたエラー値を返す
   * @return STATUS エラー値
   */
  STATUS error() const;

  /**
   * @brief 表示済みフラグが立っているか
   * @return true 表示済み
   * @return false 未表示
   */
  bool isDisplayed() const;

  /**
   * @brief リモートフラグが立っているか
   * @return true リモート
   * @return false ローカル
   */
  bool isRemote() const;

  /**
   * @brief パッケージを返す
   * @return STATUS パッケージ値
   */
  STATUS package() const;

  /**
   * @brief エラー番号を返す。
   * @return エラー番号
   */
  STATUS errnum() const;

  /**
   * @brief フラグを除くエラー値が0かどうか
   * @return true エラーがない
   * @return false エラーがある
   */
  operator bool() const;

  /**
   * @brief 例外の内容を示す文字列を返す
   * @return const char* Notes C APIエラー文字列(LMBCS)
   */
  virtual const char* what() const noexcept override;

  /**
   * @brief 例外内容をQByteArray型で返す
   * @return QByteArray 例外メッセージ
   */
  QByteArray message() const;
};

} // namespace npp090001

#endif // NPP9_0_1_STATUS_H