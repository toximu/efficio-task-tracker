#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include <QListWidget>
#include <QWidget>

class ProjectList : public QListWidget {
  Q_OBJECT
public:
  explicit ProjectList(QWidget *parent = nullptr);

signals:
};

#endif // PROJECTLIST_H
