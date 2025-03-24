#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QScreen>
#include <QStyle>
#include <QTimer>
#include <QTranslator>
#include "applicationwindow.h"
#include "login_window.h"
#include "mainwindow.h"
#include "note.hpp"
#include "registration_window.h"
#include "storage.hpp"

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

    Ui::ApplicationWindow *app_window = new Ui::ApplicationWindow("efficio");
    LoginWindow *login_window = new LoginWindow(app_window);

    app_window->setCentralWidget(login_window);
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - login_window->width()) / 2;
    int y = (screenGeometry.height() - login_window->height()) / 2;
    app_window->move(x, y);
    app_window->show();
    return a.exec();
}