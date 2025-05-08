#include "bottombar.h"
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>

namespace Ui {
BottomBar::BottomBar(
    QWidget *parent,
    std::string username,
    std::string project_name
)
    : QWidget(parent),
      main_layout_(new QHBoxLayout()),
      project_name_(new QLabel(project_name.c_str())),
      profile_button_(new QPushButton(username.c_str()))  
{
    this->setObjectName("BottomBar");
    this->setLayout(main_layout_);
    this->setFixedHeight(40);

    profile_button_->setObjectName("profile_button");
    profile_button_->setStyleSheet("background-color: transparent; text-align: right;");

    project_name_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    
    main_layout_->addWidget(project_name_);
    main_layout_->addStretch();  
    main_layout_->addWidget(profile_button_);

    connect(profile_button_, &QPushButton::clicked, 
            this, &BottomBar::profile_button_clicked);
}
}  // namespace Ui