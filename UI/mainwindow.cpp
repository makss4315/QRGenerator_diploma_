#include "mainwindow.h"
#include "mainwindow.ui"
#include "qrcodegen/UserInputs.h""

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Qstring PathToImage = QString::fromStdString(UserInputs::GetUserPathInput()+ "/" + UserInputs::GetUserFileName() + ".png");

MainWindow::~MainWindow()
{
    delete ui;
}
