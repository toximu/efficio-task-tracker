#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "login_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    if (!DatabaseManager::get_instance().check_connection()) {
        qDebug() << "Failed to connect to database!";
        return -1;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "login_window_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    LoginWindow login_window;
    login_window.show();
    return login_window.exec();
}
