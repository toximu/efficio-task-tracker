#include "projectitem.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>
#include <string>
ProjectItem::ProjectItem(std::string text_, QListWidget *list_view)
    : QListWidgetItem(text_.c_str(), list_view) {}
