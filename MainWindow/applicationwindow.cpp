#include "applicationwindow.h"
#include "mainwindow.h"

ApplicationWindow::ApplicationWindow(std::string window_name_)
    : QMainWindow{nullptr} {
  this->setWindowTitle(window_name_.c_str());
  this->resize(800, 600);
}
