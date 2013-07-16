#ifndef FLOORTILE_H
#define FLOORTILE_H

#include <QFrame>
#include "scenario.h"

namespace Ui {
class FloorTile;
}

class FloorTile : public QFrame
{
    Q_OBJECT
    
public:
    FloorTile(QWidget *parent = 0);
    ~FloorTile();
    
    //bool isBlank() const { return blank; }
    //void makeRoom(const std::shared_ptr<Room>& r);
    //std::shared_ptr<Room> makeBlank();

public slots:
    void select();
    void deselect();

signals:
    void tileClicked(FloorTile* tile);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::FloorTile *ui;
    //std::shared_ptr<Room> room;
    bool blank;
};

#endif // FLOORTILE_H
