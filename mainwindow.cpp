#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include "exception.h"
#include "registry.h"
#include "main_directory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    wTab_(new QTabWidget),
    errmsg_(new QErrorMessage)
{
    ui->setupUi(this);
    showMaximized();
    if (!ui->centralWidget->layout()) {
        QVBoxLayout *vertLayout = new QVBoxLayout();
        ui->centralWidget->setLayout(vertLayout);
    }
    ui->centralWidget->layout()->addWidget(wTab_);

    make_connections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_connections()
{
}

void MainWindow::on_newScenario_triggered()
{
    prompt_for_main_dir();
    if(!Registry<MainDirectory>::valid())
        return;
    QString name = QInputDialog::getText(this, "New Scenario",
                                         "Enter a name for the scenario");
    if (name.isEmpty()) {
        return;
    }

    setWindowTitle(name);

    Registry<Scenario>::set(std::make_shared<Scenario>(name));

    setup_tabs();

    //ui->actionSave_Scenario->setEnabled(true);
}

void MainWindow::on_loadScenario_triggered()
{
    prompt_for_main_dir();
    if(!Registry<MainDirectory>::valid())
        return;

    auto path(prompt_for_scenario_path());

    if(path.isEmpty())
        return;

    try
    {
        load_scenario(path);
        setup_tabs();
    }
    catch(ErgException& e)
    {
        errmsg_->showMessage("Error - Parsing: " + e.whatq() + " from " + path);
        return;
    }
}

QString MainWindow::prompt_for_scenario_path()
{
    return QFileDialog::getOpenFileName(this, "Select a Scenario File", Registry<MainDirectory>::instance()->js_dir(), "Scenario JSON File (*.js)");
}

void MainWindow::load_scenario(QString path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly))
    {
        throw ErgException("failed to open file: " + path);
    }

    auto bytes(file.readAll());

    strip_json_variable(bytes);

    QJsonDocument doc(QJsonDocument::fromJson(bytes));

    if(doc.isNull())
        throw ErgException("failed to parse file: " + path);

    auto obj(doc.object());
    auto name(obj.find(QString("name")));

    if(obj.end() == name)
        throw ErgException("failed to find scenario 'name'");

    setWindowTitle(name.key());

    Registry<Scenario>::set(std::make_shared<Scenario>(name.key()));

    auto scenario(Registry<Scenario>::instance());

    scenario->from_json(obj);
}

void MainWindow::strip_json_variable(QByteArray& doc)
{
    auto at(doc.indexOf('{'));

    doc.remove(0, at);
}

void MainWindow::setup_tabs()
{
    setup_floor_tab();
}

void MainWindow::setup_floor_tab()
{
    auto scenario(Registry<Scenario>::instance());

    floorwidget_.reset(new FloorWidget(this));
    connect(this, SIGNAL(load_floor(const std::shared_ptr<Floor>&)), &*floorwidget_, SLOT(load_floor(const std::shared_ptr<Floor>&)));
    int tabNum = wTab_->addTab(&(*floorwidget_), "&Floors");
    wTab_->setCurrentIndex(tabNum);

    for(auto& floor : scenario->floors())
    {
        emit load_floor(floor);
    }
}

void MainWindow::prompt_for_main_dir()
{
    if(Registry<MainDirectory>::valid())
        if(QMessageBox::Yes != QMessageBox::question(this, "Change Main Directory", "Change main directory?", QMessageBox::Yes|QMessageBox::No))
            return;

    auto path(QFileDialog::getExistingDirectory(this, "Select the Main Directory", QString()));

    if(path.isEmpty())
        return;

    Registry<MainDirectory>::set(std::make_shared<MainDirectory>(path));
}
