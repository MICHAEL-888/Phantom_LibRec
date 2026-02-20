#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);
  qDebug() << "Qt demo running";
  qDebug() << "Qt version:" << QT_VERSION_STR;
  return 0;
}
#else
int main() {
  std::printf("Qt demo (deps disabled)\n");
  return 0;
}
#endif
