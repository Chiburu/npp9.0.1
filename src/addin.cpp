#include "../include/npp9.0.1/addin.h"

namespace npp090001::addin {

void logMessageText(const QByteArray& message) {
  logMessageText(message, NOERROR);
}

} // namespace npp090001::addin