#include "member_selection_dialog.h"
#include <QDialogButtonBox>
#include <QListWidgetItem>
#include <QPainter>
#include <QRandomGenerator>
#include <QVBoxLayout>

MemberSelectionDialog::MemberSelectionDialog(
    const std::vector<std::string> &available_members,
    QWidget *parent
)
    : QDialog(parent) {
    setWindowTitle(tr("Add Members"));
    resize(300, 400);

    auto *layout = new QVBoxLayout(this);
    members_list = new QListWidget(this);

    for (const auto &member : available_members) {
        QColor color = generate_random_color(member);
        QPixmap icon = create_circle_icon(color);

        auto *item =
            new QListWidgetItem(QIcon(icon), QString::fromStdString(member));
        item->setData(Qt::UserRole, QString::fromStdString(member));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        members_list->addItem(item);
    }

    layout->addWidget(members_list);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this
    );

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);
}

QColor MemberSelectionDialog::generate_random_color(
    const std::string &seed
) const {
    // Генерируем цвет на основе хеша строки для постоянства
    uint hash = qHash(QString::fromStdString(seed));
    QRandomGenerator generator(hash);
    return QColor::fromHsv(
        generator.bounded(360), 150 + generator.bounded(80),
        200 + generator.bounded(55)
    );
}

QPixmap
MemberSelectionDialog::create_circle_icon(const QColor &color, int size) const {
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(1, 1, size - 2, size - 2);

    return pixmap;
}

std::vector<std::string> MemberSelectionDialog::get_selected_members() const {
    std::vector<std::string> selected;
    for (int i = 0; i < members_list->count(); ++i) {
        QListWidgetItem *item = members_list->item(i);
        if (item->checkState() == Qt::Checked) {
            selected.push_back(
                item->data(Qt::UserRole).toString().toStdString()
            );
        }
    }
    return selected;
}