#ifndef NPP9_0_1_HOOK_H
#define NPP9_0_1_HOOK_H

#include "npp_global.h"
#include "status.h"
#include "utils.h"
#include <optional>

PUSH_PACK1
#include <extmgr.h>
POP_PACK

namespace npp090001::hook {

/**
 * @brief フック登録クラス
 * フックしたいEM関数を登録するためのクラス
 * 静的インスタンスを MainEntryPoint(または序数1の関数) に作成し、
 * 必要であれば再帰IDを先に取得しておき、
 * 順次 install メソッドでフックを登録する。
 * @example
    struct NoteOpenHook {
      static const EID eid = EM_NSFNOTEOPENEXTENDED;
      static const DWORD regFlags = EM_REG_AFTER;
      static STATUS before(EMRECORD*) { return ERR_EM_CONTINUE; }
      static STATUS after(EMRECORD* pRec) {
        ...
        return ERR_EM_CONTINUE;
      }
    };
    struct NoteDeleteHook {...};

    extern "C"
    STATUS LNCALLBACK CallbackEntryPoint(EMRECORD *pRec) {
      ...
      return ERR_EM_CONTINUE;
    }

    extern "C"
    STATUS LNCALLBACK MainEntryPoint() {
      static npp::hook::Registration noteOpen;
      static npp::hook::Registration noteDelete;
      try {
        auto recId = npp::hook::createRecursionId();
        QStringList enabledList {"nserver", "nhttp"};
        noteOpen.install<NoteOpenHook>(enabledList, CallbackEntryPoint, recId);
        noteOpen.install<NoteDeleteHook>(enabledList, CallbackEntryPoint, recId);
      }
      catch (npp::Status& status) {
        return status.status();
      }
      return NOERROR;
    }
 * 
 */
class NPP_EXPORT Registration
{
  /**
   * @brief EM登録ハンドル
   */
  HEMREGISTRATION handle_;

public:
  static const QString& processName();

  /**
   * @brief デフォルトコンストラクタ
   */
  Registration();

  /**
   * @brief デストラクタ
   *  デタッチ時にハンドラを解放する。
   */
  virtual ~Registration();

  /**
   * @brief フックを登録する。
   * @tparam Hook フック情報型
   *  次のメンバーをパブリックレベルで定義しておく
   *    static const EID eid;
   *    static const DWORD regFlags;
   * @param handler EMHANDLER型の関数
   * @param recursionId 再帰ID、使わない場合は0を指定するか省略する。
   */
  template <class Hook>
  void install(
    EMHANDLER handler,
    WORD recursionId = 0
  ) {
    npp::Status status = EMRegister(
      Hook::eid,
      Hook::regFlags,
      handler,
      recursionId,
      &handle_
    );
    if (!status) throw status;
  }
};

/**
 * @brief 再帰IDを作成する。
 * @return WORD 再帰ID
 */
WORD NPP_EXPORT createRecursionId();

/**
 * @brief コールバックされた情報を元にフック関数を呼び出す。
 * @tparam Hook フック情報型
 *  次のメンバーをパブリックレベルで定義しておく
 *    static const EID eid;
 *    static STATUS before(EMRECORD*);
 *    static STATUS after(EMRECORD*);
 *  beforeとafterは、呼び出さない方は省略できないので、
 *  { return ERR_EM_CONTINUE; } とだけ記述する。
 * @param pRec フック引数情報へのポインタ
 * @return STATUS 呼び出したフック関数からの戻り値
 * @return std::nullopt EIDが一致しない
 * @example
    extern "C"
    STATUS LNCALLBACK CallbackEntryPoint(EMRECORD *pRec) {
      std::optional<STATUS> result;
      if (result = npp::hook::dispatch<NoteOpenHook>(pRec)) return result.value();
      if (result = npp::hook::dispatch<NoteDeleteHook>(pRec)) return result.value();
      return ERR_EM_CONTINUE;
    }
 */
template <class Hook>
std::optional<STATUS> dispatch(EMRECORD *pRec) {
  return npp::opt_tree<STATUS>(
    [&pRec] { return pRec->EId == Hook::eid; },
    [&pRec] {
      return pRec->NotificationType == EM_BEFORE
        ? Hook::before(pRec)
        : Hook::after(pRec);
    }
  );
}

} // namespace npp090001::hook

#endif // NPP9_0_1_HOOK_H