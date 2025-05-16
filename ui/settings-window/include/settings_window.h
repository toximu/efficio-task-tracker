#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QApplication>

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    void handle_theme_changed(int theme);
    static const std::vector<QString> THEMES;

private slots:
    void toggle_language();
    void toggle_theme();
    void set_small_font();
    void set_medium_font();
    void set_large_font();

private:
    void update_ui_text();

    QVBoxLayout* main_layout;
    QPushButton *language_button;
    QPushButton *theme_button;
    QLabel *title_label;
    QLabel *font_size_label;
    QRadioButton *small_font_radio;
    QRadioButton *medium_font_radio;
    QRadioButton *large_font_radio;
};

#endif // SETTINGS_WINDOW_H