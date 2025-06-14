#include <bits/std_thread.h>
#include <grpcpp/create_channel.h>
#include <QApplication>
#include <QLibraryInfo>
#include <QScreen>
#include "client_implementation.h"
#include "language_manager.h"
#include "login_window.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    ClientImplementation client(
        CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())
    );

    const auto app_window = new QMainWindow();
    app_window->setWindowTitle("EFFICIO");
    auto *login_window = new LoginWindow(&client, app_window);

    app_window->setCentralWidget(login_window);
    const QRect screen_geometry =
        QApplication::primaryScreen()->availableGeometry();
    const int x = (screen_geometry.width() - login_window->width()) / 2;
    const int y = (screen_geometry.height() - login_window->height()) / 2;
    app_window->move(x, y);
    app_window->show();

    QApplication::exec();

    return 0;
}