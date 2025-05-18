#ifndef ANALYTICS_DIALOG_H
#define ANALYTICS_DIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <vector>

class AnalyticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalyticsWindow(QWidget *parent = nullptr);
    ~AnalyticsWindow();

    void setTasksData(int created, int completed, int overdue);
    void setProjectsData(const QMap<QString, int>& projects);
    void handle_theme_changed(int theme);
    void handle_font_size_changed(std::string font_size);
    void on_switch_theme_clicked();
    
    static const std::vector<QString> THEMES;

private:
    QTabWidget *tab_widget;
    QVBoxLayout *tasks_layout;
    QVBoxLayout *projects_layout;
    QDialogButtonBox *button_box;

    QChart *createTasksChart(int created, int completed, int overdue);
    QChart *createProjectsChart(const QMap<QString, int>& projects);
};

#endif // ANALYTICS_DIALOG_H