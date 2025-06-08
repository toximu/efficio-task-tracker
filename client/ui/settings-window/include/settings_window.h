#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent);
    void handle_theme_changed(int theme_);
    void handle_font_size_changed(std::string font_size_);
    void handle_language_changed(std::string new_language);
    static const std::vector<QString> THEMES;

private slots:
    void toggle_language();
    void toggle_theme();
    void set_small_font();
    void set_medium_font();
    void set_big_font();

private:
    void update_ui_text();

    QVBoxLayout *main_layout;
    QPushButton *language_button;
    QPushButton *theme_button;
    QLabel *title_label;
    QLabel *font_size_label;
    QRadioButton *small_font_radio;
    QRadioButton *medium_font_radio;
    QRadioButton *large_font_radio;
};

#endif  // SETTINGS_WINDOW_H