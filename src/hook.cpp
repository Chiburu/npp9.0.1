#include "../include/npp9.0.1/hook.h"
#include "../include/npp9.0.1/os.h"
#include "../include/npp9.0.1/path.h"
#include "../include/npp9.0.1/utils.h"
#include "../include/npp9.0.1/status.h"

namespace npp090001::hook {

const QString& Registration::processName() {
  static QString name_ = path::getFileName(os::getProcessPath());
  return name_;
}

Registration::Registration()
  : handle_(NULLHANDLE)
{}

Registration::~Registration() {
#ifdef _WIN32
  // 経験上LinuxでEMDeregisterを呼び出すとコンソールに余計な情報が表示される
  tree(
    [this] { return handle_ != NULLHANDLE; },
    [this] { EMDeregister(handle_); }
  );
#endif
}

WORD createRecursionId() {
  WORD recId = 0;
  Status status = EMCreateRecursionID(&recId);
  if (!status) throw status;
  return recId;
}

} // namespace npp090001::hook
