#include "language_manager.h"
#include <QApplication>
#include <QWidget>
#include <string>

LanguageManager *LanguageManager::m_instance = nullptr;

LanguageManager::LanguageManager(QObject *parent) : QObject(parent) {
    std::string language = "RU";
    apply_language(language);
}

LanguageManager *LanguageManager::instance() {
    if (!m_instance) {
        m_instance = new LanguageManager();
    }
    return m_instance;
}

void LanguageManager::apply_language(std::string new_language_) {
    this->current_language_ = new_language_;
    emit language_changed(this->current_language_);
}

std::string LanguageManager::current_language() const {
    return current_language_;
}