#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>

class ApplicationWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit ApplicationWindow(std::string window_name);

signals:
};

#endif // APPLICATIONWINDOW_H
