#include "projectlist.h"
#include <QListWidget>
ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
  this->setObjectName("ProjectList");
  this->setMaximumWidth(200);
}
