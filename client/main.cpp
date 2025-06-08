#include <bits/std_thread.h>
#include <grpcpp/create_channel.h>
#include <QApplication>
#include <QLocale>
#include <QScreen>
#include <QTranslator>
#include "applicationwindow.h"
#include "client_implementation.h"
// #include "login_window.h"
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

    ClientImplementation client(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()
    ));

    auto *app_window = new Ui::ApplicationWindow("EFFICIO");
    std::unique_ptr<User> usr = std::make_unique<User>();
    usr->set_login("toximu");
    usr->set_hashed_password("12345678");
    client.try_authenticate_user(usr.get());
    Ui::MainWindow window(app_window, std::move(usr), &client);
    app_window->setCentralWidget(&window);
    app_window->resize(800, 600);
    app_window->show();

    // auto *login_window = new LoginWindow(app_window);
    //
    // app_window->setCentralWidget(login_window);
    // const QRect screen_geometry =
    //     QApplication::primaryScreen()->availableGeometry();
    // const int x = (screen_geometry.width() - login_window->width()) / 2;
    // const int y = (screen_geometry.height() - login_window->height()) / 2;
    // app_window->move(x, y);
    // app_window->show();
    int exit_code = QApplication::exec();
    client.complete_rpc_thread_.join();
}