#include <QApplication>
#include <QLocale>
#include <QStyleFactory>
#include <QTranslator>
#include <thread>
#include "client_implementation.h"
#include "note_edit_dialog.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QTranslator translator;
    const QStringList ui_languages = QLocale::system().uiLanguages();

    for (const QString &locale : ui_languages) {
        const QString base_name = "NoteWidgetEfficio_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + base_name)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }

    const auto channel =
        CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    ClientImplementation client(channel);

    std::thread requests([&] {
        try {
            client.CompleteRpc();
        } catch (const std::exception &e) {
            std::cout << "[CLIENT ERROR]: " << e.what() << std::endl;
        }
    });
    requests.detach();

    const auto test_note = new Note();
    client.create_note(test_note);

    NoteEditDialog dialog(&client, nullptr, test_note);
    dialog.show();
    return QApplication::exec();
}