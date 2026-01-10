#include "mainwindow.h"
#include "mainwindow.ui"
#include "qrcodegen/UserInputs.h"
#include "QPixmap"





QString PathToImage = QString::fromStdString(UserInputs::GetUserPathInput()+ "/" + UserInputs::GetUserFileName() + ".png");

QPixmap pix(PathToImage);



MainWindow::MainWindow(QWidget *parent)



    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}
