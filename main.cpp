#include <QApplication>
#include "base.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(files);

  QApplication app(argc, argv);
  Base base;
  return app.exec();
}
