#ifndef STYLE_MANAGER_H
#define STYLE_MANAGER_H

#include <QMap>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QVector>
#include <string>

class StyleManager : public QObject {
    Q_OBJECT

public:
    static StyleManager *instance();

    void apply_theme(int theme);
    void apply_font_size(std::string font_size_);
    int current_theme() const;
    std::string current_font_size() const;
signals:
    void theme_changed(int new_theme);
    void font_size_changed(std::string new_font_size_);

private:
    explicit StyleManager(QObject *parent = nullptr);
    static StyleManager *m_instance;
    int current_theme_;
    std::string current_font_size_;
};

#endif  // style_manager_H