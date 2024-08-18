#include "../include/npp9.0.1/path.h"
#include <QFileInfo>

namespace npp090001::path {

QString getFileName(const QString &path) {
  QFileInfo fileInfo(path);
  return fileInfo.baseName();
}

} // namespace npp090001::path
