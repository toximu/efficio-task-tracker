#include "analytics_window.h"
#include <QString>
#include "analytics_window_style_sheet.h"
#include "language_manager.h"
#include "style_manager.h"

const std::vector<QString> AnalyticsWindow::THEMES = {
    Ui::analytics_window_light_autumn_theme,
    Ui::analytics_window_dark_autumn_theme,
    Ui::analytics_window_dark_purple_theme,
    Ui::analytics_window_light_purple_theme, Ui::analytics_window_blue_theme
};

AnalyticsWindow::AnalyticsWindow(
    QWidget *parent,
    const int created_count,
    const int completed_count,
    const int expired_count
)
    : QDialog(parent),
      m_created_count(created_count),
      m_completed_count(completed_count),
      m_expired_count(expired_count),
      chart_view(new QChartView(this)),
      series(new QPieSeries()),
      chart(new QChart()) {
    setFixedSize(700, 400);

    QVBoxLayout *main_layout = new QVBoxLayout(this);

    completed_slice = new QPieSlice();
    completed_slice->setValue(m_completed_count);
    completed_slice->setColor(QColor(46, 204, 113));

    expired_slice = new QPieSlice();
    expired_slice->setValue(m_expired_count);
    expired_slice->setColor(QColor(231, 76, 60));

    created_slice = new QPieSlice();
    created_slice->setValue(m_created_count);
    created_slice->setColor(QColor(52, 152, 219));

    series->append(completed_slice);
    series->append(expired_slice);
    series->append(created_slice);

    chart->addSeries(series);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);

    chart_view->setRenderHint(QPainter::Antialiasing);
    chart_view->setChart(chart);

    main_layout->addWidget(chart_view);
    setLayout(main_layout);

    connect(
        StyleManager::instance(), &StyleManager::theme_changed, this,
        &AnalyticsWindow::handle_theme_changed
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed, this,
        &AnalyticsWindow::handle_font_size_changed
    );
    connect(
        LanguageManager::instance(), &LanguageManager::language_changed, this,
        &AnalyticsWindow::handle_language_changed
    );
    handle_font_size_changed(StyleManager::instance()->current_font_size());
    handle_theme_changed(StyleManager::instance()->current_theme());
    handle_language_changed(LanguageManager::instance()->current_language());
}

void AnalyticsWindow::setup_chart() const {
    series->append("Завершенные", m_completed_count);
    series->append("Просроченные", m_expired_count);
    series->append("Созданные", m_created_count);

    QPieSlice *completed_slice = series->slices().at(0);
    completed_slice->setColor(QColor(46, 204, 113));
    completed_slice->setLabelVisible(true);

    QPieSlice *expired_slice = series->slices().at(1);
    expired_slice->setColor(QColor(231, 76, 60));
    expired_slice->setLabelVisible(true);

    QPieSlice *created_slice = series->slices().at(2);
    created_slice->setColor(QColor(52, 152, 219));
    created_slice->setLabelVisible(true);

    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(
            slice->label() + QString(": %1 (%2%)")
                                 .arg(slice->value())
                                 .arg(100 * slice->percentage(), 0, 'f', 1)
        );
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Статистика заметок");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);

    chart_view->setChart(chart);
}

AnalyticsWindow::~AnalyticsWindow() {
}

void AnalyticsWindow::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        chart->setTitle("Статистика заметок");
        completed_slice->setLabel("Завершенные");
        expired_slice->setLabel("Просроченные");
        created_slice->setLabel("Актуальные");
        setWindowTitle("Аналитическая панель");
    } else if (new_language == "EN") {
        chart->setTitle("Notes Statistics");
        completed_slice->setLabel("Completed");
        expired_slice->setLabel("Expired");
        created_slice->setLabel("Actual");
        setWindowTitle("Analytics Panel");
    }
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(true);
        QString label =
            slice->label() + QString(": %1 (%2%)")
                                 .arg(slice->value())
                                 .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }
}

void AnalyticsWindow::handle_font_size_changed(std::string font_size) {
    QString font_size_rule;
    if (font_size == "small") {
        font_size_rule = "QPushButton { font-size: 11px; }";
    } else if (font_size == "medium") {
        font_size_rule = "QPushButton { font-size: 13px; }";
    } else if (font_size == "big") {
        font_size_rule = "QPushButton { font-size: 15px; }";
    }

    this->setStyleSheet(
        THEMES[StyleManager::instance()->current_theme()] + font_size_rule
    );
}

void AnalyticsWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void AnalyticsWindow::on_switch_theme_clicked() {
    int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
    StyleManager::instance()->apply_theme(next_theme);
}