#include "bottombar.h"
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QSpacerItem>

namespace Ui {
BottomBar::BottomBar(
    QWidget *parent,
    const std::string& username,
    QString project_name
)
    : QWidget(parent),
      main_layout_(new QHBoxLayout()),
      project_name_(new QLabel(project_name)),
      profile_button_(new QPushButton(username.c_str()))  
{
    this->setObjectName("BottomBar");
    this->setLayout(main_layout_);
    this->setFixedHeight(40);

    profile_button_->setObjectName("profile_button");

    project_name_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    
    main_layout_->addWidget(project_name_);
    main_layout_->addStretch();  
    main_layout_->addWidget(profile_button_);

    connect(profile_button_, &QPushButton::clicked, 
            this, &BottomBar::profile_button_clicked);
    
    this->setLayout(main_layout_);
    this->setAttribute(Qt::WA_StyledBackground);
}
}  // namespace Ui