#ifndef style_manager_H
#define style_manager_H

#include <QMap>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QVector>
#include <string>

class LanguageManager : public QObject {
    Q_OBJECT

public:
    static LanguageManager *instance();

    void apply_language(std::string new_language_);
    std::string current_language() const;

signals:
    void language_changed(std::string new_language_);

private:
    explicit LanguageManager(QObject *parent = nullptr);
    static LanguageManager *m_instance;
    std::string current_language_;
};

#endif  // style_manager_H