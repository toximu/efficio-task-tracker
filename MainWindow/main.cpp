#include "mainwindow.h"
#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget *window = new Widget();

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "MainWindow_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  MainWindow *main_window = new MainWindow();

  main_window->show();
  // window->show();
  return a.exec();
}
