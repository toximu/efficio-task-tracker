#include "theme_manager.h"
#include <QApplication>
#include <QWidget>

ThemeManager *ThemeManager::instance_ = nullptr;

ThemeManager::ThemeManager(QObject *parent) : QObject(parent) {
    current_theme_ = 0;
    emit on_theme_changed(this->current_theme_);
}

ThemeManager *ThemeManager::get_instance() {
    if (!instance_) {
        instance_ = new ThemeManager();
    }
    return instance_;
}

void ThemeManager::apply_theme(const int theme) {
    this->current_theme_ = theme;
    emit on_theme_changed(this->current_theme_);
}

int ThemeManager::get_current_theme() const {
    return current_theme_;
}