#include "../include/npp9.0.1/fs.h"
#include <QFileInfo>
#include <QDir>

namespace npp090001::fs {

void mkdir(const QString& filePath) {
  QFileInfo info(filePath);
  auto dir = info.dir();
  if (!dir.exists()) {
    dir.mkpath(dir.path());
  }
}

} // namespace npp090001::fs
