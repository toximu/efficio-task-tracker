#include <QApplication>
#include <QLocale>
#include <QStyleFactory>
#include <QTranslator>
#include "database_manager.hpp"
#include "note_edit_dialog.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    if (!DatabaseManager::get_instance().check_connection()) {
        qDebug() << "Failed to connect to database!";
        return -1;
    }

    QTranslator translator;
    const QStringList ui_languages = QLocale::system().uiLanguages();

    for (const QString &locale : ui_languages) {
        const QString base_name = "NoteWidgetEfficio_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + base_name)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }

    NoteEditDialog dialog;
    dialog.show();
    return QApplication::exec();
}
