#include "../include/npp9.0.1/env.h"

PUSH_PACK1
#include <global.h>
#include <osenv.h>
#include <osfile.h>
#include <names.h>
POP_PACK

namespace npp090001::env {

QByteArray getString(
  const char *key,
  std::function<QByteArray()> fn
) {
  char buffer[MAXENVVALUE + 1];
  return OSGetEnvironmentString(key, buffer, MAXENVVALUE)
    ? QByteArray(buffer)
    : fn();
}

QByteArray getString(
  const QByteArray& key,
  std::function<QByteArray()> fn
) {
  return getString(key.constData(), fn);
}

QByteArray getString(
  const char *key,
  const QByteArray& defaultValue
) {
  return getString(key, [&defaultValue] { return defaultValue; });
}

QByteArray getString(
  const QByteArray& key,
  const QByteArray& defaultValue
) {
  return getString(key, [&defaultValue] { return defaultValue; });
}

QByteArray getDataDirectory() {
  char path[MAXPATH] = "";
  WORD len = OSGetDataDirectory(path);
  return QByteArray(path, len);
}

} // namespace npp090001::env
