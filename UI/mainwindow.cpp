#include "mainwindow.h"
#include "mainwindow.ui"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Qstring

MainWindow::~MainWindow()
{
    delete ui;
}
