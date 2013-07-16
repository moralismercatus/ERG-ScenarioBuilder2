#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

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
    
private slots:
    void on_newScenario_triggered();

    void on_loadScenario_triggered();

protected:
    void setup_tabs();
    void setup_floor_tab();
    QString query_scenario_path();
    void load_scenario(QString path);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QTabWidget> wTab_;
    std::unique_ptr<FloorWidget> floorwidget_;
};

#endif // MAINWINDOW_H
