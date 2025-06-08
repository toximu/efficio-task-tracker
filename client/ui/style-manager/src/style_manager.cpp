#include "style_manager.h"
#include <QApplication>
#include <QWidget>
#include <string>

StyleManager *StyleManager::m_instance = nullptr;

StyleManager::StyleManager(QObject *parent) : QObject(parent) {
    current_theme_ = 0;
    emit theme_changed(this->current_theme_);
}

StyleManager *StyleManager::instance() {
    if (!m_instance) {
        m_instance = new StyleManager();
    }
    return m_instance;
}

void StyleManager::apply_theme(int theme) {
    this->current_theme_ = theme;
    emit theme_changed(this->current_theme_);
}

int StyleManager::current_theme() const {
    return current_theme_;
}

void StyleManager::apply_font_size(std::string font_size_) {
    current_font_size_ = font_size_;
    emit font_size_changed(current_font_size_);
}

std::string StyleManager::current_font_size() const {
    return current_font_size_;
}