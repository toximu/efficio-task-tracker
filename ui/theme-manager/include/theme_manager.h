#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSettings>
#include <QMap>

class ThemeManager : public QObject {
    Q_OBJECT

public:
    static ThemeManager* instance();
    
    void apply_theme(int theme);
    int current_theme() const;

signals:
    void theme_changed(int new_theme);

private:
    explicit ThemeManager(QObject *parent = nullptr);
    static ThemeManager* m_instance;
    int current_theme_;
};

#endif // THEME_MANAGER_H