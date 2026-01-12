#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "qr_handler.h"






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
void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();

    if (text.isEmpty())
        return;

    QString filePath = "text.png";

    generateQrPng(
        text.toStdString(),
        filePath.toStdString()
    );

    QPixmap pixmap(filePath);

    if (pixmap.isNull()) {
        return;
    }

    ui->label->setPixmap(
        pixmap.scaled(
            ui->label->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation)
            );
}