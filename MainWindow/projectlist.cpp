#include "projectlist.h"
#include"widget.h"
#include<QListWidget>
ProjectList::ProjectList(Widget *parent)
    : QListWidget{parent}
{
    this->setMaximumWidth(200);
}
