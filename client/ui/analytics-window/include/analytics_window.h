#ifndef ANALYTICS_DIALOG_H
#define ANALYTICS_DIALOG_H

#include <QChartView>
#include <QtCharts>
#include <vector>

class AnalyticsWindow final : public QDialog {
    Q_OBJECT

public:
    explicit AnalyticsWindow(
        QWidget *parent = nullptr,
        int created_count = 0,
        int completed_count = 0,
        int expired_count = 0
    );
    ~AnalyticsWindow() override;

    static const std::vector<QString> THEMES;

private:
    void handle_theme_changed(int theme);
    void handle_font_size_changed(std::string font_size);
    void handle_language_changed(std::string new_language);
    void on_switch_theme_clicked();
    void setup_chart() const;

    int m_created_count;
    int m_completed_count;
    int m_expired_count;

    QChartView *chart_view;
    QPieSeries *series;
    QChart *chart;
    QPieSlice *completed_slice;
    QPieSlice *expired_slice;
    QPieSlice *created_slice;
};

#endif  // ANALYTICS_DIALOG_H