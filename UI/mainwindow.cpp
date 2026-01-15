#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "qr_handler.h"
#include "QFileDialog"
#include "QMessageBox"






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

void MainWindow::on_saveButton_clicked(){
    if (ui->label->pixmap().isNull()) {
        QMessageBox::warning(this, "Error","no QR to save");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
    this,
    "Save QR-Code",
    "",
    "PNG Image (*.png)"
    );

    if (filePath.isEmpty()) {
        return;
    };

    ui->label->pixmap().save(filePath, "png");
}

void MainWindow::on_generateButton_clicked()
{
    QString text = ui->textEdit->toPlainText();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "No text to QR");
        return;
    }

    QString tempPath = QDir::tempPath()+ "/qr_temp.png";

    generateQrPng(
        text.toStdString(),
        tempPath.toStdString()
    );

    QPixmap pixmap(tempPath);

    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "Can not load QR-code");
        return;
    }

    ui->label->setPixmap(
        pixmap.scaled(
            ui->label->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation)
            );
}

