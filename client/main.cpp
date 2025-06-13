#include <bits/std_thread.h>
#include <grpcpp/create_channel.h>
#include <QApplication>
#include <QLibraryInfo>
#include <QScreen>
#include <QTranslator>
#include "client_implementation.h"
#include "language_manager.h"
#include "login_window.h"
#include "style_manager.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    // application.setApplicationName("EFFICIO");
    // application.setApplicationDisplayName("EFFICIO");
    // application.setOrganizationName("EFFICIO");
    // application.setWindowIcon(QIcon(":/icons/app_icon.png"));
    //
    // QTranslator appTranslator;
    // QTranslator qtTranslator;
    //
    // const QSettings settings;
    // const QString language =
    //     settings.value("Language", QLocale::system().name()).toString();
    //
    // if (appTranslator.load(":/translations/app_" + language + ".qm")) {
    //     application.installTranslator(&appTranslator);
    // }

    // if (qtTranslator.load(
    //         "qt_" + language,
    //         QLibraryInfo::path(QLibraryInfo::TranslationsPath)
    //     )) {
    //     application.installTranslator(&qtTranslator);
    // }

    ClientImplementation client(
        CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
    );
    std::cout << "do" << std::endl;
    std::cout << "donee" << std::endl;
    const auto app_window = new QMainWindow();
    app_window->setWindowTitle("EFFICIO");
    // auto *login_window = new LoginWindow(&client, app_window);
    std::cout << "donee" << std::endl;
    // app_window->setCentralWidget(login_window);
    const QRect screen_geometry =
        QApplication::primaryScreen()->availableGeometry();
    // const int x = (screen_geometry.width() - login_window->width()) / 2;
    // const int y = (screen_geometry.height() - login_window->height()) / 2;
    // app_window->move(x, y);
    app_window->show();
    std::cout << "donee" << std::endl;
    QApplication::exec();
    std::cout << "done" << std::endl;
    return 0;
}