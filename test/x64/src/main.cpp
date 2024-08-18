#include "../../../include/npp9.0.1/addin.h"

namespace npp = npp090001;

extern "C"
STATUS LNPUBLIC	AddInMain(HMODULE, int, char**) {
  npp::addin::logMessageText("Hello npp9.0.1 addin!");
  return 0;
}
