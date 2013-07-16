#include <QDebug>

#include "floortile.h"
#include "ui_floortile.h"

FloorTile::FloorTile(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FloorTile),
    //room(NULL),
    blank(true)
{
    ui->setupUi(this);
    setFrameStyle(QFrame::Box | QFrame::Plain);

    ui->x->setValidator(new QIntValidator());
    ui->y->setValidator(new QIntValidator());

    ui->roomFrame->hide();
    ui->walls->addItem("North");
    ui->walls->addItem("East");
    ui->walls->addItem("South");
    ui->walls->addItem("West");
}

FloorTile::~FloorTile()
{
    delete ui;
}

//void FloorTile::makeRoom(const std::shared_ptr<Room>& r)
//{
//    room = r;
//    ui->roomFrame->show();
//    ui->walls->show();
//    ui->name->setText(r->name);
//    ui->x->setText(QString::number(r->x));
//    ui->y->setText(QString::number(r->y));
//    blank = false;
//}

//std::shared_ptr<Room> FloorTile::makeBlank()
//{
//    auto r = room;
//    room.reset();
//    ui->name->setText("");
//    ui->x->setText("");
//    ui->y->setText("");
//    ui->roomFrame->hide();
//    ui->walls->hide();
//    blank = true;
//    return r;
//}

void FloorTile::select()
{
    setLineWidth(5);
    update();
}

void FloorTile::deselect()
{
    setLineWidth(1);
    update();
}

void FloorTile::mousePressEvent(QMouseEvent *event)
{
    emit tileClicked(this);

    QFrame::mousePressEvent(event);
}
