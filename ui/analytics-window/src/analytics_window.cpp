#include "analytics_dialog.h"

AnalyticsWindow::AnalyticsWindow(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    
    tab_widget = new Qtab_widget(this);
    
    QWidget *tasks_tab = new QWidget();
    tasks_layout = new QVBoxLayout(tasks_tab);
    tab_widget->addTab(tasks_tab, "Статистика задач");
    
    QWidget *projects_tab = new QWidget();
    projects_layout = new QVBoxLayout(projects_tab);
    tab_widget->addTab(projects_tab, "Распределение по проектам");
    
    button_box = new QDialogbutton_box(QDialogbutton_box::Close, this);
    connect(button_box, &QDialogbutton_box::rejected, this, &QDialog::reject);
    
    main_layout->addWidget(tab_widget);
    main_layout->addWidget(button_box);
    
    setWindowTitle("Аналитическая панель");
    resize(800, 600);
    
    setTasksData(0, 0, 0);
    
    QMap<QString, int> projects;
    setProjectsData(projects);
}

AnalyticsWindow::~AnalyticsWindow()
{
    delete this;
}

void AnalyticsWindow::setTasksData(int created, int completed, int overdue)
{
    QLayoutItem *child;
    while (child = tasks_layout->takeAt(0)) {
        delete child->widget();
        delete child;
    }
    
    QChart *chart = createTasksChart(created, completed, overdue);
    tasks_layout->addWidget(new QChartView(chart));
}

void AnalyticsWindow::setProjectsData(const QMap<QString, int>& projects)
{
    QLayoutItem *child;
    while (child = projects_layout->takeAt(0)) {
        delete child->widget();
        delete child;
    }
    
    QChart *chart = createProjectsChart(projects);
    projects_layout->addWidget(new QChartView(chart));
}

QChart* AnalyticsWindow::createTasksChart(int created, int completed, int overdue)
{
    QBarSet *created_set = new QBarSet("Создано");
    *created_set << created;
    
    QBarSet *completed_set = new QBarSet("Завершено");
    *completed_set << completed;
    
    QBarSet *overdue_set = new QBarSet("Просрочено");
    *overdue_set << overdue;

    QBarSeries *series = new QBarSeries();
    series->append(created_set);
    series->append(completed_set);
    series->append(overdue_set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Статистика задач за период");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append("Тип задач");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int maxValue = qMax(created, qMax(completed, overdue));
    axisY->setRange(0, maxValue + (maxValue * 0.1)); // +10% отмакс. значения
    axisY->setTitleText("Количество");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return chart;
}

QChart* AnalyticsWindow::createProjectsChart(const QMap<QString, int>& projects)
{
    QPieSeries *series = new QPieSeries();
    
    int total = 0;
    for (auto it = projects.begin(); it != projects.end(); ++it) {
        series->append(it.key(), it.value());
        total += it.value();
    }

    series->setLabelsVisible();
    foreach(QPieSlice *slice, series->slices()) {
        slice->setLabel(QString("%1 (%2%)")
                      .arg(slice->label())
                      .arg(100 * slice->percentage(), 0, 'f', 1));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString("Распределение задач (%1 всего)").arg(total));
    chart->legend()->setAlignment(Qt::AlignRight);

    return chart;
}