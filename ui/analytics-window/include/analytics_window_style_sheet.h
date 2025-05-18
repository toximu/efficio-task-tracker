#ifndef ANALYTICS_WINDOW_STYLE_SHEET_H
#define ANALYTICS_WINDOW_STYLE_SHEET_H

#include <QString>

namespace Ui {

const QString analytics_window_light_autumn_theme = R"(
#AnalyticsWindow {
    background-color: #f5f5f5;
    color: #444444;
    font-family: 'Arial';
}

QTabWidget::pane {
    border: 1px solid #d0d0d0;
    border-radius: 4px;
    margin: 5px;
    background: #ffffff;
}

QTabBar::tab {
    background: #e0e0e0;
    color: #666666;
    border: 1px solid #d0d0d0;
    border-bottom: none;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
    padding: 8px 15px;
    margin-right: 2px;
}

QTabBar::tab:selected {
    background: #ffffff;
    color: #222222;
    border-color: #d0d0d0;
    font-weight: bold;
}

QTabBar::tab:hover {
    background: #f0f0f0;
}

QDialogButtonBox {
    border-top: 1px solid #d0d0d0;
    padding-top: 10px;
}

QDialogButtonBox QPushButton {
    background-color: #fea36b;
    color: white;
    border: 1px solid #e08c52;
    border-radius: 3px;
    padding: 5px 15px;
    min-width: 80px;
}

QDialogButtonBox QPushButton:hover {
    background-color: #f58c50;
}

QDialogButtonBox QPushButton:pressed {
    background-color: #e07c40;
}

QChartView {
    background-color: #ffffff;
    border-radius: 5px;
    border: 1px solid #d0d0d0;
    margin: 10px;
}

QLegend::label {
    color: #666666;
}

QAbstractAxis {
    color: #888888;
}
)";

const QString analytics_window_dark_autumn_theme = R"(
#AnalyticsWindow {
    background-color: #202020;
    color: #BDD1BD;
    font-family: 'Arial';
}

QTabWidget::pane {
    border: 1px solid #333333;
    border-radius: 4px;
    margin: 5px;
    background: #282828;
}

QTabBar::tab {
    background: #323232;
    color: #8a8a8a;
    border: 1px solid #333333;
    border-bottom: none;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
    padding: 8px 15px;
    margin-right: 2px;
}

QTabBar::tab:selected {
    background: #3a3a3a;
    color: #BDD1BD;
    border-color: #333333;
    font-weight: bold;
}

QTabBar::tab:hover {
    background: #363636;
}

QDialogButtonBox {
    border-top: 1px solid #333333;
    padding-top: 10px;
}

QDialogButtonBox QPushButton {
    background-color: #d38b5f;
    color: #263238;
    border: 1px solid #b3754d;
    border-radius: 3px;
    padding: 5px 15px;
    min-width: 80px;
}

QDialogButtonBox QPushButton:hover {
    background-color: #c07b4f;
}

QDialogButtonBox QPushButton:pressed {
    background-color: #a86b3f;
}

QChartView {
    background-color: #282828;
    border-radius: 5px;
    border: 1px solid #333333;
    margin: 10px;
}

QLegend::label {
    color: #a0a0a0;
}

QAbstractAxis {
    color: #8a8a8a;
}
)";

const QString analytics_window_light_purple_theme = R"(
#AnalyticsWindow {
    background-color: #9882B9;
    color: rgb(42, 10, 25);
    font-family: 'Arial';
}

QTabWidget::pane {
    border: 1px solid #7a5d9b;
    border-radius: 4px;
    margin: 5px;
    background: #b9a2d9;
}

QTabBar::tab {
    background: #a992c9;
    color: rgb(62, 20, 35);
    border: 1px solid #7a5d9b;
    border-bottom: none;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
    padding: 8px 15px;
    margin-right: 2px;
}

QTabBar::tab:selected {
    background: #d9c2f9;
    color: rgb(42, 10, 25);
    border-color: #7a5d9b;
    font-weight: bold;
}

QTabBar::tab:hover {
    background: #c9b2e9;
}

QDialogButtonBox {
    border-top: 1px solid #7a5d9b;
    padding-top: 10px;
}

QDialogButtonBox QPushButton {
    background-color: #722548;
    color: #f5e5ff;
    border: 1px solid #5a1538;
    border-radius: 3px;
    padding: 5px 15px;
    min-width: 80px;
}

QDialogButtonBox QPushButton:hover {
    background-color: #5a1538;
}

QDialogButtonBox QPushButton:pressed {
    background-color: #4a0528;
}

QChartView {
    background-color: #d9c2f9;
    border-radius: 5px;
    border: 1px solid #7a5d9b;
    margin: 10px;
}

QLegend::label {
    color: rgb(62, 20, 35);
}

QAbstractAxis {
    color: rgb(82, 40, 55);
}
)";

const QString analytics_window_dark_purple_theme = R"(
#AnalyticsWindow {
    background-color: #221932;
    color: #9882B9;
    font-family: 'Arial';
}

QTabWidget::pane {
    border: 1px solid #3a2a4a;
    border-radius: 4px;
    margin: 5px;
    background: #2a1f3a;
}

QTabBar::tab {
    background: #322242;
    color: #7a6a9a;
    border: 1px solid #3a2a4a;
    border-bottom: none;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
    padding: 8px 15px;
    margin-right: 2px;
}

QTabBar::tab:selected {
    background: #4a3a5a;
    color: #c9b2e9;
    border-color: #5a4a6a;
    font-weight: bold;
}

QTabBar::tab:hover {
    background: #3a2a4a;
}

QDialogButtonBox {
    border-top: 1px solid #3a2a4a;
    padding-top: 10px;
}

QDialogButtonBox QPushButton {
    background-color: #722548;
    color: #d9c2f9;
    border: 1px solid #5a1538;
    border-radius: 3px;
    padding: 5px 15px;
    min-width: 80px;
}

QDialogButtonBox QPushButton:hover {
    background-color: #5a1538;
}

QDialogButtonBox QPushButton:pressed {
    background-color: #4a0528;
}

QChartView {
    background-color: #322242;
    border-radius: 5px;
    border: 1px solid #3a2a4a;
    margin: 10px;
}

QLegend::label {
    color: #9a82b9;
}

QAbstractAxis {
    color: #8a7aa9;
}
)";

const QString analytics_window_blue_theme = R"(
#AnalyticsWindow {
    background-color: #07142B;
    color: #BDD1BD;
    font-family: 'Arial';
}

QTabWidget::pane {
    border: 1px solid #1a2c4b;
    border-radius: 4px;
    margin: 5px;
    background: #0f1c35;
}

QTabBar::tab {
    background: #173C4C;
    color: #8dacbd;
    border: 1px solid #1a2c4b;
    border-bottom: none;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
    padding: 8px 15px;
    margin-right: 2px;
}

QTabBar::tab:selected {
    background: #1f4c5c;
    color: #BDD1BD;
    border-color: #1a2c4b;
    font-weight: bold;
}

QTabBar::tab:hover {
    background: #1b4454;
}

QDialogButtonBox {
    border-top: 1px solid #1a2c4b;
    padding-top: 10px;
}

QDialogButtonBox QPushButton {
    background-color: #568F7C;
    color: #07142B;
    border: 1px solid #3a6f5c;
    border-radius: 3px;
    padding: 5px 15px;
    min-width: 80px;
}

QDialogButtonBox QPushButton:hover {
    background-color: #3a6f5c;
}

QDialogButtonBox QPushButton:pressed {
    background-color: #2a5f4c;
}

QChartView {
    background-color: #0f1c35;
    border-radius: 5px;
    border: 1px solid #1a2c4b;
    margin: 10px;
}

QLegend::label {
    color: #9dbdcd;
}

QAbstractAxis {
    color: #7d9cad;
}
)";

} // namespace Ui

#endif // ANALYTICS_WINDOW_STYLE_SHEET_H