#include "theme_manager.h"
#include <QApplication>
#include <QWidget>

ThemeManager* ThemeManager::m_instance = nullptr;

ThemeManager::ThemeManager(QObject *parent) 
    : QObject(parent) {
    current_theme_ = 0;
    emit theme_changed(this->current_theme_);
}

ThemeManager* ThemeManager::instance() {
    if (!m_instance) {
        m_instance = new ThemeManager();
    }
    return m_instance;
}

void ThemeManager::apply_theme(int theme) {
    this->current_theme_ = theme;
    emit theme_changed(this->current_theme_);
}

int ThemeManager::current_theme() const {
    return current_theme_;
}