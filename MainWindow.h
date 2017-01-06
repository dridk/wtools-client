#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FieldsModel.h"
#include "VariantModel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public Q_SLOTS:
    void load();

private:
    Ui::MainWindow *ui;

    FieldsModel * mModel;
    VariantModel * mVariantModel;
};

#endif // MAINWINDOW_H
