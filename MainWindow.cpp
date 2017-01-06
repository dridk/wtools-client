#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new FieldsModel;
    mVariantModel = new VariantModel;
    ui->treeView->setModel(mModel);
    ui->tableView->setModel(mVariantModel);


    connect(ui->actionLoad, SIGNAL(triggered(bool)), mModel,SLOT(load()));

    connect(ui->actionRun, SIGNAL(triggered(bool)), this,SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    mVariantModel->setFields(mModel->fields());
    mVariantModel->load();


}
