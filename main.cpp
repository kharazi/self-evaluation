#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(files);

  QApplication app(argc, argv);

  QApplication::setQuitOnLastWindowClosed(false);

  MainWidget window;
  //window.show();
  return app.exec();
}
