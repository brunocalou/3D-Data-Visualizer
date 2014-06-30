#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->widget->setMouseTracking(true);
//    ui->widget->setFocusPolicy(Qt::MouseFocusReason);
}

MainWindow::~MainWindow()
{
    delete ui;
}
