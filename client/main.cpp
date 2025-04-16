#include <QApplication>
#include <QLocale>
#include <QStyleFactory>
#include <QTranslator>
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

    NoteEditDialog dialog(nullptr, new Note);
    dialog.show();
    return QApplication::exec();
}