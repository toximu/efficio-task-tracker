#include "../include/applicationwindow.h"
#include "../include/mainwindow.h"
#include <QPalette>

namespace Ui {
ApplicationWindow::ApplicationWindow(std::string window_name_)
    : QMainWindow{nullptr} {
  this->setObjectName("ApplicationWindow");

  this->setAttribute(Qt::WA_StyledBackground);

  this->setWindowTitle(window_name_.c_str());
  this->resize(800, 600);
}
} // namespace Ui
