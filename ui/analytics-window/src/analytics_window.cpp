#include "analytics_window.h"
#include "style_manager.h"
#include "language_manager.h"
#include "analytics_window_style_sheet.h"
#include <QString>

const std::vector<QString> AnalyticsWindow::THEMES = {
    Ui::analytics_window_light_autumn_theme,
    Ui::analytics_window_dark_autumn_theme,
    Ui::analytics_window_dark_purple_theme,
    Ui::analytics_window_light_purple_theme,
    Ui::analytics_window_blue_theme
};

AnalyticsWindow::AnalyticsWindow(QWidget *parent, 
                                 int created_count, 
                                 int completed_count, 
                                 int expired_count)
    : QDialog(parent),
      m_created_count(created_count),
      m_completed_count(completed_count),
      m_expired_count(expired_count),
      chart_view(new QChartView(this)),
      series(new QPieSeries()),
      chart(new QChart())
{
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
        StyleManager::instance(), &StyleManager::theme_changed,
        this, &AnalyticsWindow::handle_theme_changed
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed,
        this, &AnalyticsWindow::handle_font_size_changed
    );
    connect(LanguageManager::instance(), &LanguageManager::language_changed,
            this, &AnalyticsWindow::handle_language_changed
    );
    handle_font_size_changed(StyleManager::instance()->current_font_size());
    handle_theme_changed(StyleManager::instance()->current_theme());
    handle_language_changed(LanguageManager::instance()->current_language());
}

void AnalyticsWindow::setup_chart()
{
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
    
    for(QPieSlice *slice : series->slices()) {
        slice->setLabel(slice->label() + 
                       QString(": %1 (%2%)")
                       .arg(slice->value())
                       .arg(100 * slice->percentage(), 0, 'f', 1));
    }
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Статистика заметок");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    
    chart_view->setChart(chart);
}

AnalyticsWindow::~AnalyticsWindow(){}

void AnalyticsWindow::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        chart->setTitle("Статистика заметок");
        completed_slice->setLabel("Завершенные");
        expired_slice->setLabel("Просроченные");
        created_slice->setLabel("Созданные");
        setWindowTitle("Аналитическая панель");
    } 
    else if (new_language == "EN") {
        chart->setTitle("Notes Statistics");
        completed_slice->setLabel("Completed");
        expired_slice->setLabel("Expired");
        created_slice->setLabel("Created");
        setWindowTitle("Analytics Panel");
    }
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(true);
        QString label = slice->label() + 
                       QString(": %1 (%2%)")
                       .arg(slice->value())
                       .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }
}

void AnalyticsWindow::handle_font_size_changed(std::string font_size) {
    
    QString font_size_rule;
    if(font_size == "small") {
        font_size_rule = "QPushButton { font-size: 11px; }";
    } 
    else if(font_size == "medium") {
        font_size_rule = "QPushButton { font-size: 13px; }";
    } 
    else if(font_size == "big") {
        font_size_rule = "QPushButton { font-size: 15px; }";
    }
    
    this->setStyleSheet(THEMES[StyleManager::instance()->current_theme()] + font_size_rule);
}

void AnalyticsWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void AnalyticsWindow::on_switch_theme_clicked() {
    int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
    StyleManager::instance()->apply_theme(next_theme);
}






// #include "analytics_window.h"
// #include "style_manager.h"
// #include "language_manager.h"
// #include "analytics_window_style_sheet.h"
// #include <QString>

// const std::vector<QString> AnalyticsWindow::THEMES = {
//     Ui::analytics_window_light_autumn_theme,
//     Ui::analytics_window_dark_autumn_theme,
//     Ui::analytics_window_dark_purple_theme,
//     Ui::analytics_window_light_purple_theme,
//     Ui::analytics_window_blue_theme
// };

// AnalyticsWindow::AnalyticsWindow(QWidget *parent)
//     : QDialog(parent)
// {
//     QVBoxLayout *main_layout = new QVBoxLayout(this);
    
//     tab_widget = new QTabWidget(this);
    
//     QWidget *tasks_tab = new QWidget();
//     tasks_layout = new QVBoxLayout(tasks_tab);
//     tab_widget->addTab(tasks_tab, "Статистика задач");
    
//     QWidget *projects_tab = new QWidget();
//     projects_layout = new QVBoxLayout(projects_tab);
//     tab_widget->addTab(projects_tab, "Распределение по проектам");
    
//     button_box = new QDialogButtonBox(QDialogButtonBox::Close, this);
//     connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
//     main_layout->addWidget(tab_widget);
//     main_layout->addWidget(button_box);
    
//     setWindowTitle("Аналитическая панель");
//     resize(800, 600);
    
//     setTasksData(0, 0, 0);
    
//     QMap<QString, int> projects;
//     setProjectsData(projects);

//     connect(StyleManager::instance(), &StyleManager::theme_changed,
//             this, &AnalyticsWindow::handle_theme_changed);    
//     handle_theme_changed(StyleManager::instance()->current_theme());
//     connect(StyleManager::instance(), &StyleManager::font_size_changed,
//             this, &AnalyticsWindow::handle_font_size_changed
//     );
//     handle_font_size_changed(StyleManager::instance()->current_font_size());

//     connect(LanguageManager::instance(), &LanguageManager::language_changed,
//             this, &AnalyticsWindow::handle_language_changed
//     );
//     handle_language_changed(LanguageManager::instance()->current_language());
// }


// void AnalyticsWindow::handle_language_changed(std::string new_language) {
//     if (new_language == "RU") {
//         tab_widget->setTabText(0, tr("Статистика задач"));
//         tab_widget->setTabText(1, tr("Распределение по проектам"));
//         setWindowTitle(tr("Аналитическая панель"));
        
//         QChart *tasks_chart = static_cast<QChartView*>(tasks_layout->itemAt(0)->widget())->chart();
//         tasks_chart->setTitle(tr("Статистика задач за период"));
//         static_cast<QValueAxis*>(tasks_chart->axes(Qt::Vertical)[0])->setTitleText(tr("Количество"));
        
//         QBarSeries *tasks_series = static_cast<QBarSeries*>(tasks_chart->series()[0]);
//         static_cast<QBarSet*>(tasks_series->barSets()[0])->setLabel(tr("Создано"));
//         static_cast<QBarSet*>(tasks_series->barSets()[1])->setLabel(tr("Завершено"));
//         static_cast<QBarSet*>(tasks_series->barSets()[2])->setLabel(tr("Просрочено"));
        
//         button_box->button(QDialogButtonBox::Close)->setText(tr("Закрыть"));
//     } 
//     else if(new_language == "EN") {
//         tab_widget->setTabText(0, tr("Tasks Statistics"));
//         tab_widget->setTabText(1, tr("Projects Distribution"));
//         setWindowTitle(tr("Analytics Panel"));
        
//         QChart *tasks_chart = static_cast<QChartView*>(tasks_layout->itemAt(0)->widget())->chart();
//         tasks_chart->setTitle(tr("Tasks Statistics for Period"));
//         static_cast<QValueAxis*>(tasks_chart->axes(Qt::Vertical)[0])->setTitleText(tr("Count"));
        
//         QBarSeries *tasks_series = static_cast<QBarSeries*>(tasks_chart->series()[0]);
//         static_cast<QBarSet*>(tasks_series->barSets()[0])->setLabel(tr("Created"));
//         static_cast<QBarSet*>(tasks_series->barSets()[1])->setLabel(tr("Completed"));
//         static_cast<QBarSet*>(tasks_series->barSets()[2])->setLabel(tr("Overdue"));
        
//         button_box->button(QDialogButtonBox::Close)->setText(tr("Close"));
//     } 
// }

// void AnalyticsWindow::handle_font_size_changed(std::string font_size) {
    
//     QString font_size_rule;
//     if(font_size == "small") {
//         font_size_rule = "QPushButton { font-size: 11px; }";
//     } 
//     else if(font_size == "medium") {
//         font_size_rule = "QPushButton { font-size: 13px; }";
//     } 
//     else if(font_size == "big") {
//         font_size_rule = "QPushButton { font-size: 15px; }";
//     }
    
//     this->setStyleSheet(THEMES[StyleManager::instance()->current_theme()] + font_size_rule);
// }

// void AnalyticsWindow::handle_theme_changed(int theme) {
//     this->setStyleSheet(THEMES[theme]);
// }

// void AnalyticsWindow::on_switch_theme_clicked() {
//     int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
//     StyleManager::instance()->apply_theme(next_theme);
// }

// AnalyticsWindow::~AnalyticsWindow(){}

// void AnalyticsWindow::setTasksData(int created, int completed, int overdue)
// {
//     QLayoutItem *child;
//     while (child = tasks_layout->takeAt(0)) {
//         delete child->widget();
//         delete child;
//     }
    
//     QChart *chart = createTasksChart(created, completed, overdue);
//     tasks_layout->addWidget(new QChartView(chart));
// }

// void AnalyticsWindow::setProjectsData(const QMap<QString, int>& projects)
// {
//     QLayoutItem *child;
//     while (child = projects_layout->takeAt(0)) {
//         delete child->widget();
//         delete child;
//     }
    
//     QChart *chart = createProjectsChart(projects);
//     projects_layout->addWidget(new QChartView(chart));
// }

// QChart* AnalyticsWindow::createTasksChart(int created, int completed, int overdue)
// {
//     QBarSet *created_set = new QBarSet("Создано");
//     *created_set << created;
    
//     QBarSet *completed_set = new QBarSet("Завершено");
//     *completed_set << completed;
    
//     QBarSet *overdue_set = new QBarSet("Просрочено");
//     *overdue_set << overdue;

//     QBarSeries *series = new QBarSeries();
//     series->append(created_set);
//     series->append(completed_set);
//     series->append(overdue_set);

//     QChart *chart = new QChart();
//     chart->addSeries(series);
//     chart->setTitle("Статистика задач за период");
//     chart->setAnimationOptions(QChart::SeriesAnimations);

//     QBarCategoryAxis *axisX = new QBarCategoryAxis();
//     axisX->append("Тип задач");
//     chart->addAxis(axisX, Qt::AlignBottom);
//     series->attachAxis(axisX);

//     QValueAxis *axisY = new QValueAxis();
//     int maxValue = qMax(created, qMax(completed, overdue));
//     axisY->setRange(0, maxValue + (maxValue * 0.1)); // +10% отмакс. значения
//     axisY->setTitleText("Количество");
//     chart->addAxis(axisY, Qt::AlignLeft);
//     series->attachAxis(axisY);

//     return chart;
// }

// QChart* AnalyticsWindow::createProjectsChart(const QMap<QString, int>& projects)
// {
//     QPieSeries *series = new QPieSeries();
    
//     int total = 0;
//     for (auto it = projects.begin(); it != projects.end(); ++it) {
//         series->append(it.key(), it.value());
//         total += it.value();
//     }

//     series->setLabelsVisible();
//     foreach(QPieSlice *slice, series->slices()) {
//         slice->setLabel(QString("%1 (%2%)")
//                       .arg(slice->label())
//                       .arg(100 * slice->percentage(), 0, 'f', 1));
//     }

//     QChart *chart = new QChart();
//     chart->addSeries(series);
//     chart->setTitle(QString("Распределение задач (%1 всего)").arg(total));
//     chart->legend()->setAlignment(Qt::AlignRight);

//     return chart;
// }