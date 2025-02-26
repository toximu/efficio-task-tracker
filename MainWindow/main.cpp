#include "applicationwindow.h"
#include "mainwindow.h"
#include "project.hpp"
#include <QApplication>
#include <QLabel>
#include <QLocale>
#include <QTranslator>
#include"note.hpp"
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
  MainWindow *main_window = new MainWindow(nullptr,"username");
  app_window->setCentralWidget(main_window);

  project_storage_model::Project *p1 =
      new project_storage_model::Project(1, "one", "");
  project_storage_model::Project *p2 =
      new project_storage_model::Project(1, "two", "");
  project_storage_model::Project *p3 =
      new project_storage_model::Project(1, "five", "");
  main_window->add_project(p1);
  main_window->add_project(p2);
  main_window->add_project(p3);

  project_storage_model::Note n1 = project_storage_model::Note(1, "first", "some text");
  project_storage_model::Note n2 = project_storage_model::Note(1, "second", "some texttt");
  project_storage_model::Note n3 = project_storage_model::Note(1, "first", "some text");
  project_storage_model::Note n4 = project_storage_model::Note(1, "second", "some texttt");
  p1->add_note(n1);
  p1->add_note(n2);
  p1->add_note(n3);
  p1->add_note(n4);





  app_window->show();

  return a.exec();
  delete app_window;
  delete p1, p2, p3;
  return 0;
}
