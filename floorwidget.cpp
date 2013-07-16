#include "floorwidget.h"
#include "ui_floorwidget.h"
#include "floortile.h"

#include <QInputDialog>

FloorWidget::FloorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloorWidget)
{
    ui->setupUi(this);
}

FloorWidget::~FloorWidget()
{
    delete ui;
}

void FloorWidget::on_newFloor_clicked()
{
    // TODO: check name is valid
    QString name = QInputDialog::getText(this, "New Floor",
                                         "Enter a name for the floor");
    if (name.isEmpty()) {
        return;
    }

    if(-1 != ui->floorSelector->findText(name))
        return;

    ui->floorSelector->addItem(name);
    ui->floorSelector->setEnabled(true);
    auto idx(ui->floorSelector->findText(name));
    ui->floorSelector->setCurrentIndex(idx);
}

void FloorWidget::on_floorSelector_currentIndexChanged(const QString& floor)
{
    setup_floor();
    update_floor_name(floor);
}

void FloorWidget::setup_floor()
{
//    setup_floor_grid();
    create_blank_tiles();
}

void FloorWidget::update_floor_name(const QString& floor)
{
    ui->floorName->setText(floor);
}

void FloorWidget::setup_floor_grid()
{/*
    auto layout(new QGridLayout);

    layout->setObjectName(QString("grid"));

    ui->scrollAreaWidgetContents->setLayout(layout);*/
}

void FloorWidget::create_blank_tiles()
{
    for (int i = 0; i < DEFAULT_FLOOR_GRID_SIZE; ++i) {
        for (int j = 0; j < DEFAULT_FLOOR_GRID_SIZE; ++j) {
            FloorTile *t = new FloorTile();
            ui->grid->addWidget(t, i, j);

            //connect(t, SIGNAL(tileClicked(FloorTile*)),
                    //nthis, SLOT(tileClicked(FloorTile*)));
        }
    }
    //int sw = ui->scrollArea->verticalScrollBar()->width();
    ui->scrollArea->setMaximumSize(DEFAULT_FLOOR_GRID_SIZE * 222 /*+ sw*/, DEFAULT_FLOOR_GRID_SIZE * 222 /*+ sw*/);
}
