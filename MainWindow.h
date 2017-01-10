#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "FieldsModel.h"
#include "VariantModel.h"
#include "LogicView.h"

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

    void showQuery();

private:
    Ui::MainWindow *ui;

    FieldsModel * mModel;
    VariantModel * mVariantModel;
    LogicView* mLogicView;
    QPlainTextEdit * mEdit;
};

#endif // MAINWINDOW_H
