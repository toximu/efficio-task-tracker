#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include "applicationwindow.h"
#include "mainwindow.h"
#include "note.hpp"
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

    LoginWindow login_window;
    login_window.show();
    return login_window.exec();
}