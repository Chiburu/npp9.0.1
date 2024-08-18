#include "../include/npp9.0.1/os.h"

#ifdef _WIN32
# include <Windows.h>
#else // Linux
# include <unistd.h>
#endif

namespace npp090001::os {

QString getProcessPath() {
#ifdef _WIN32
  WCHAR buffer[MAX_PATH] = L"";
  auto size = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
  if (size > 0) {
    // 成功時
    return QString::fromWCharArray(buffer, size);
  } else {
    // 失敗時
    return QString();
  }
#else // Linux
  char buffer[1024] = "";
  auto len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  return QString::fromUtf8(buffer, len);
#endif
}

} // namespace npp090001::os
