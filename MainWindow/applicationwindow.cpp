#include "applicationwindow.h"
#include "mainwindow.h"
#include<QPalette>
ApplicationWindow::ApplicationWindow(std::string window_name_)
    : QMainWindow{nullptr} {
    this->setObjectName("ApplicationWindow");
    // this->setWindowFlags(Qt::FramelessWindowHint);
    // this->setAttribute(Qt::WA_TranslucentBackground);

  this->setWindowTitle(window_name_.c_str());
  this->resize(800, 600);
}
