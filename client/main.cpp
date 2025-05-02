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
    client.try_create_note(test_note);

    const auto new_note = new Note();
    new_note->set_id(6);
    client.try_fetch_note(new_note);

    NoteEditDialog dialog(&client, nullptr, test_note);
    dialog.show();
    return QApplication::exec();
}