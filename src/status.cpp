#include "../include/npp9.0.1/status.h"

PUSH_PACK1
#include <misc.h>
#include <osmisc.h>
POP_PACK

namespace npp090001 {

Status::Status()
  : std::exception()
  , status_(NOERROR)
{}

Status::Status(STATUS status)
  : std::exception()
  , status_(status)
{}

STATUS Status::error() const {
  return ERR(status_);
}

bool Status::isDisplayed() const {
  return ERROR_DISPLAYED(status_);
}

bool Status::isRemote() const {
  return ERROR_REMOTE(status_);
}

STATUS Status::package() const {
  return PKG(status_);
}

STATUS Status::errnum() const {
  return ERRNUM(status_);
}

Status::operator bool() const {
  return error() == NOERROR;
}

const char *Status::what() const noexcept {
  static char buffer[MAXSPRINTF + 1] = "";
  auto len = OSLoadString(NULLHANDLE, error(), buffer, MAXSPRINTF);
  buffer[len] = '\0';
  return buffer;
}

QByteArray Status::message() const {
  return QByteArray(what());
}

} // namespace npp090001
