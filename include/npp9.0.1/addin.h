#ifndef NPP9_0_1_ADDIN_H
#define NPP9_0_1_ADDIN_H

#include "npp_global.h"
#include <QByteArray>

PUSH_PACK1
#include <global.h>
#include <addin.h>
POP_PACK

namespace npp090001::addin {

/**
 * @brief AddInLogMessageText のラッパー関数
 * @tparam Args 可変長引数型
 * @param message メッセージバイト配列
 * @param status 追加ステータス
 * @param args 可変長引数
 */
template <class... Args>
void logMessageText(
  const QByteArray& message,
  STATUS status,
  Args... args
) {
  AddInLogMessageText(
    const_cast<char*>(message.constData()),
    status,
    args...
  );
}

/**
 * @brief メッセージバイト配列をコンソールに出力する。
 * @param message メッセージバイト配列
 */
void NPP_EXPORT logMessageText(const QByteArray& message);

} // namespace npp090001::addin

#endif // NPP9_0_1_ADDIN_H