#include "applicationwindow.h"
#include "mainwindow.h"
#include "note.hpp"
#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include "storage.hpp"

using namespace Ui;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "MainWindow_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  project_storage_model::Storage storage;
  ApplicationWindow *app_window = new ApplicationWindow("efficio");
  MainWindow *main_window = new MainWindow(app_window, "username", &storage);
  app_window->setCentralWidget(main_window);

  app_window->show();

  return a.exec();
  delete app_window;

  return 0;
}
