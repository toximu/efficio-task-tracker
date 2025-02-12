#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include <string>
class Project; // not have yet

class ProjectItem : public QListWidgetItem {
  Project *project;

public:
  ProjectItem(std::string text,QListWidget *listview);
};

#endif // PROJECTITEM_H
