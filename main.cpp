#include <QApplication>
#include <QLocale>
#include <QScreen>
#include <QTranslator>
#include <QSettings>
#include "applicationwindow.h"
#include "login_window.h"
#include "theme_manager.h"
#include <QLibraryInfo>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setApplicationName("EFFICIO");
    app.setApplicationDisplayName("EFFICIO");
    app.setOrganizationName("EFFICIO");
    app.setWindowIcon(QIcon(":/icons/app_icon.png"));

    QTranslator appTranslator;
    QTranslator qtTranslator;
    
    QSettings settings;
    QString language = settings.value("Language", QLocale::system().name()).toString();
    
    if (appTranslator.load(":/translations/app_" + language + ".qm")) {
        app.installTranslator(&appTranslator);
    }
    
    if (qtTranslator.load("qt_" + language, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        app.installTranslator(&qtTranslator);
    }

    ThemeManager* themeManager = ThemeManager::instance();
    
    QMainWindow *app_window = new QMainWindow();
    app_window->setWindowTitle("EFFICIO"); 
    auto *login_window = new LoginWindow(app_window);

    app_window->setCentralWidget(login_window);
    const QRect screen_geometry = QApplication::primaryScreen()->availableGeometry();
    const int x = (screen_geometry.width() - login_window->width()) / 2;
    const int y = (screen_geometry.height() - login_window->height()) / 2;
    app_window->move(x, y);
    app_window->show();

    return app.exec();

}