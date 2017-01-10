#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new FieldsModel;
    mVariantModel = new VariantModel;
    mLogicView = new LogicView;
    mEdit = new QPlainTextEdit;

    ui->treeView->setModel(mModel);
    ui->tableView->setModel(mVariantModel);

    QDockWidget * test = new QDockWidget ;
    test->setWidget(mLogicView);


    addDockWidget(Qt::RightDockWidgetArea, test);


    connect(ui->actionLoad, SIGNAL(triggered(bool)), mModel,SLOT(load()));
    connect(ui->actionLoad, SIGNAL(triggered(bool)), mLogicView,SLOT(load()));

    connect(ui->actionRun, SIGNAL(triggered(bool)), this,SLOT(load()));


    connect(ui->actionQuery, SIGNAL(triggered(bool)), this,SLOT(showQuery()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    mVariantModel->setFields(mModel->fields());
    mVariantModel->setQuery(mLogicView->query());
    mVariantModel->load();


}

void MainWindow::showQuery()
{

    mEdit->setPlainText(mLogicView->query());

    mEdit->show();


}
