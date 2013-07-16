#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QErrorMessage>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    wTab_(new QTabWidget)
{
    ui->setupUi(this);
    showMaximized();
    if (!ui->centralWidget->layout()) {
        QVBoxLayout *vertLayout = new QVBoxLayout();
        ui->centralWidget->setLayout(vertLayout);
    }
    ui->centralWidget->layout()->addWidget(&(*wTab_));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newScenario_triggered()
{
    QString name = QInputDialog::getText(this, "New Scenario",
                                         "Enter a name for the scenario");
    if (name.isEmpty()) {
        return;
    }

    setWindowTitle(name);

    Registry::set(std::make_shared<Scenario>(name));

    setup_tabs();

    //ui->actionSave_Scenario->setEnabled(true);
}

void MainWindow::on_loadScenario_triggered()
{
    auto path(query_scenario_path());

    if(path.isEmpty())
        return;

    setup_tabs();
    load_scenario(path);
}

QString MainWindow::query_scenario_path()
{
    return QFileDialog::getOpenFileName(this, "Select a Scenario File", QString(), "Scenario JSON File (*.js)");
}

void MainWindow::load_scenario(QString path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly))
    {
        QErrorMessage msg(this);
        msg.showMessage("Failed to open file: " + path);
        return;
    }

    auto bytes(file.readAll());

    QJsonDocument doc(QJsonDocument::fromJson(bytes));

    auto obj(doc.object());
    auto sname(obj.value(QString("name")).toString());
    auto name(obj.find(QString("name")));


    //setWindowTitle(obj.);

    Registry::set(std::make_shared<Scenario>(sname));

    auto scenario(Registry::instance());

    scenario->from_json(obj);
}

void MainWindow::setup_tabs()
{
    setup_floor_tab();
}

void MainWindow::setup_floor_tab()
{
    floorwidget_.reset(new FloorWidget(this));
    int tabNum = wTab_->addTab(&(*floorwidget_), "Floors");
    wTab_->setCurrentIndex(tabNum);
}
