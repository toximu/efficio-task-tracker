#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <QSettings>

class ThemeManager final : public QObject {
    Q_OBJECT

public:
    static ThemeManager *get_instance();
    void apply_theme(int theme);
    [[nodiscard]] int get_current_theme() const;

signals:
    void on_theme_changed(int new_theme);

private:
    explicit ThemeManager(QObject *parent = nullptr);
    static ThemeManager *instance_;
    int current_theme_;
};

#endif  // THEME_MANAGER_H