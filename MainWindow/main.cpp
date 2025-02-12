#include "applicationwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // QWidget *window = new QWidget();

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "MainWindow_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  ApplicationWindow *app_window = new ApplicationWindow("efficio");
  MainWindow *main_window = new MainWindow(app_window, "tima");
  app_window->setCentralWidget(main_window);

  main_window->add_project("one");
  main_window->add_project("two");
  main_window->add_project("three");

  app_window->show();
  return a.exec();
  delete app_window;
}
