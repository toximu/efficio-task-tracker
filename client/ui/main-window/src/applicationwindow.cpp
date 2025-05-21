#include "applicationwindow.h"
#include <QPalette>

namespace Ui {
ApplicationWindow::ApplicationWindow(const std::string &window_name_)
    : QMainWindow{nullptr} {
    this->setObjectName("ApplicationWindow");

    this->setAttribute(Qt::WA_StyledBackground);

    this->setWindowTitle(window_name_.c_str());
}
}  // namespace Ui