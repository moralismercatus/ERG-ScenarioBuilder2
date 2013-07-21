#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QErrorMessage>

#include "scenario.h"
#include "floorwidget.h"

#include <memory>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void load_floor(const std::shared_ptr<Floor>& floor);
    
private slots:
    void on_newScenario_triggered();

    void on_loadScenario_triggered();

protected:
    void make_connections();
    void setup_tabs();
    void setup_floor_tab();
    QString prompt_for_scenario_path();
    void load_scenario(QString path);
    void strip_json_variable(QByteArray& doc);
    void prompt_for_main_dir();

private:
    Ui::MainWindow *ui;
    QTabWidget* wTab_;
    std::unique_ptr<FloorWidget> floorwidget_;
    std::unique_ptr<QErrorMessage> errmsg_;
};

#endif // MAINWINDOW_H
