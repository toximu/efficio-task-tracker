#include "applicationwindow.h"
#include <QPalette>
#include "mainwindow.h"

namespace Ui {
ApplicationWindow::ApplicationWindow(std::string window_name_)
    : QMainWindow{nullptr} {
    this->setObjectName("ApplicationWindow");

    this->setAttribute(Qt::WA_StyledBackground);

    this->setWindowTitle(window_name_.c_str());
}
}  // namespace Ui
