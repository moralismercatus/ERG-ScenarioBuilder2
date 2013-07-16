#ifndef FLOORWIDGET_H
#define FLOORWIDGET_H

#include <QWidget>

#include <memory>

#include "scenario.h"

namespace Ui {
class FloorWidget;
}

class FloorWidget : public QWidget
{
    Q_OBJECT
public:
    static const unsigned DEFAULT_FLOOR_GRID_SIZE = 3;
    
public:
    explicit FloorWidget( QWidget *parent = 0);
    ~FloorWidget();

protected:
    void setup_floor();
    void setup_floor_grid();
    void update_floor_name(const QString& floor);
    void create_blank_tiles();
    
private slots:
    void on_newFloor_clicked();

    void on_floorSelector_currentIndexChanged(const QString &arg1);

private:
    Ui::FloorWidget* ui;

};

#endif // FLOORWIDGET_H
