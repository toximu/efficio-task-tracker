#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class ApplicationWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ApplicationWindow(const std::string &window_name);

signals:
};
}  // namespace Ui
#endif  // APPLICATIONWINDOW_H