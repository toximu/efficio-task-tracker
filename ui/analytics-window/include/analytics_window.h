#ifndef ANALYTICS_DIALOG_H
#define ANALYTICS_DIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class AnalyticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyticsWindow(QWidget *parent = nullptr);
    ~AnalyticsWindow();

    void setTasksData(int created, int completed, int overdue);
    void setProjectsData(const QMap<QString, int>& projects);

private:
    QTabWidget *tab_widget;
    QVBoxLayout *tasks_layout;
    QVBoxLayout *projects_layout;
    QDialogButtonBox *button_box;

    QChart *createTasksChart(int created, int completed, int overdue);
    QChart *createProjectsChart(const QMap<QString, int>& projects);
};

#endif // ANALYTICS_DIALOG_H