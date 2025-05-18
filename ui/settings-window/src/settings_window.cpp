#include "settings_window.h"
#include "settings_window_style_sheet.h"
#include "style_manager.h"
#include <QRegularExpression>

const std::vector<QString> SettingsWindow::THEMES = {
    Ui::settings_window_light_autumn_theme,
    Ui::settings_window_dark_autumn_theme,
    Ui::settings_window_dark_purple_theme,
    Ui::settings_window_light_purple_theme,
    Ui::settings_window_blue_theme
};

SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent) {
    main_layout = new QVBoxLayout(this);

    title_label = new QLabel(tr("Настройки"), this);
    title_label->setObjectName("title_label");
    title_label->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(title_label);

    QHBoxLayout *buttons_layout = new QHBoxLayout();
    
    language_button = new QPushButton(tr("RU"), this);
    language_button->setObjectName("language_button");

    theme_button = new QPushButton(tr("Тема"), this);
    theme_button->setObjectName("theme_button");

    buttons_layout->addWidget(language_button);
    buttons_layout->addWidget(theme_button);
    main_layout->addLayout(buttons_layout);

    font_size_label = new QLabel(tr("Размер шрифта"), this);
    main_layout->addWidget(font_size_label);

    QButtonGroup *font_group = new QButtonGroup(this);
    small_font_radio = new QRadioButton(tr("Мелкий"), this);
    medium_font_radio = new QRadioButton(tr("Средний"), this);
    large_font_radio = new QRadioButton(tr("Крупный"), this);

    font_group->addButton(small_font_radio);
    font_group->addButton(medium_font_radio);
    font_group->addButton(large_font_radio);
    medium_font_radio->setChecked(true);

    QVBoxLayout *font_layout = new QVBoxLayout();
    font_layout->addWidget(small_font_radio);
    font_layout->addWidget(medium_font_radio);
    font_layout->addWidget(large_font_radio);
    main_layout->addLayout(font_layout);

    connect(language_button, &QPushButton::clicked, this, &SettingsWindow::toggle_language);
    connect(theme_button, &QPushButton::clicked, this, &SettingsWindow::toggle_theme);
    connect(small_font_radio, &QRadioButton::clicked, this, &SettingsWindow::set_small_font);
    connect(medium_font_radio, &QRadioButton::clicked, this, &SettingsWindow::set_medium_font);
    connect(large_font_radio, &QRadioButton::clicked, this, &SettingsWindow::set_big_font);
    connect(StyleManager::instance(), &StyleManager::theme_changed,
            this, &SettingsWindow::handle_theme_changed);
    connect(StyleManager::instance(), &StyleManager::font_size_changed,
            this, &SettingsWindow::handle_font_size_changed
    );
    title_label->setText(tr("Настройки"));
    font_size_label->setText(tr("Размер шрифта"));
    theme_button->setText(tr("Тема"));
    small_font_radio->setText(tr("Мелкий"));
    medium_font_radio->setText(tr("Средний"));
    large_font_radio->setText(tr("Крупный"));
    
    language_button->setText(tr("RU")); 
    setWindowTitle(tr("Настройки"));

    setLayout(main_layout);
    setFixedSize(250, 250);
    handle_theme_changed(StyleManager::instance()->current_theme());
    
    handle_font_size_changed(StyleManager::instance()->current_font_size());
}

void SettingsWindow::handle_font_size_changed(std::string font_size) {
    QString font_rule;
    if(font_size == "small") {
        font_rule = 
            "QPushButton#language_button, QPushButton#theme_button { font-size: 12px; }"
            "QWidget { font-size: 12px; }"
            "QLabel#title_label { font-size: 23px; }"
            "QLabel#font_size_label { font-size: 30px; }";
    }
    else if(font_size == "medium") {
        font_rule = 
            "QPushButton#language_button, QPushButton#theme_button  { font-size: 15px; }"
            "QWidget { font-size: 15px; }"
            "QLabel#title_label { font-size: 28px; }"
            "QLabel#font_size_label { font-size: 35px; }";
    }
    else if(font_size == "big") {
        font_rule = 
            "QPushButton#language_button, QPushButton#theme_button  { font-size: 18px; }"
            "QWidget { font-size: 18px; }"
            "QLabel#title_label { font-size: 32px; }"
            "QLabel#font_size_label { font-size: 40px; }";
    }
    this->setStyleSheet(THEMES[StyleManager::instance()->current_theme()] + font_rule);
}

void SettingsWindow::handle_theme_changed(int theme_) {
    this->setStyleSheet(THEMES[theme_]);
}

void SettingsWindow::toggle_language() {
    if (language_button->text() == tr("RU")) {
        language_button->setText(tr("EN"));
    } else {
        language_button->setText(tr("RU"));
    }
}

void SettingsWindow::toggle_theme() {
    int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
    StyleManager::instance()->apply_theme(next_theme);
}

void SettingsWindow::set_small_font() { 
    StyleManager::instance()->apply_font_size("small");
    }
void SettingsWindow::set_medium_font() { 
    StyleManager::instance()->apply_font_size("medium");
    }
void SettingsWindow::set_big_font() { 
    StyleManager::instance()->apply_font_size("big");
    }