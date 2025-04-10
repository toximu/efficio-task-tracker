#include <QApplication>
#include <QLocale>
#include <QScreen>
#include <QTimer>
#include <QTranslator>
#include "applicationwindow.h"
#include "login_window.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QTranslator translator;
    const QStringList ui_languages = QLocale::system().uiLanguages();
    for (const QString &locale : ui_languages) {
        const QString base_name = "MainWindow_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + base_name)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }

    auto *app_window = new Ui::ApplicationWindow("EFFICIO");
    auto *login_window = new LoginWindow(app_window);

    app_window->setCentralWidget(login_window);
    const QRect screen_geometry = QApplication::primaryScreen()->availableGeometry();
    const int x = (screen_geometry.width() - login_window->width()) / 2;
    const int y = (screen_geometry.height() - login_window->height()) / 2;
    app_window->move(x, y);
    app_window->show();

    return QApplication::exec();
}
