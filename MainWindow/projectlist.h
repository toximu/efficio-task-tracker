#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include <QWidget>
#include<QListWidget>
#include"widget.h"

class ProjectList : public QListWidget
{
    Q_OBJECT
public:
    explicit ProjectList(Widget *parent = nullptr);

signals:
};

#endif // PROJECTLIST_H
