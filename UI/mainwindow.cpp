#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/opencv.hpp>


#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>


#include "qr_handler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());           //lock window size - but its still dynamic for new  QT component
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    //history bar animation

    historyDock = new QDockWidget("History", this);
    historyDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    historyDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    historyList = new QListWidget(historyDock);
    historyList->setIconSize(QSize(64, 64));
    historyList->setSpacing(6);

    historyDock->setWidget(historyList);
    addDockWidget(Qt::BottomDockWidgetArea, historyDock);
    historyDock->hide();

    connect(historyList, &QListWidget::itemClicked,
            this, &MainWindow::onHistoryItemClicked);

    //  Sidebar animation
    int topOffset = ui->menuButton->height();
    ui->sideBar->move(-ui->sideBar->width(), topOffset);

    sideBarAnim = new QPropertyAnimation(ui->sideBar, "pos", this);
    sideBarAnim->setDuration(250);
    sideBarAnim->setEasingCurve(QEasingCurve::OutCubic);


    loadHistoryFromFile();


}

MainWindow::~MainWindow()
{
    saveHistoryToFile();
    delete ui;
}


void MainWindow::on_menuButton_clicked()    //"hamburger" button
{
    int topOffset = ui->menuButton->height();
    QPoint startPos = ui->sideBar->pos();
    QPoint endPos;

    if (startPos.x() < 0)
        endPos = QPoint(0, topOffset);
    else
        endPos = QPoint(-ui->sideBar->width(), topOffset);

    sideBarAnim->stop();
    sideBarAnim->setStartValue(startPos);
    sideBarAnim->setEndValue(endPos);
    sideBarAnim->start();
}

void MainWindow::on_historyButton_clicked()
{
    int h = 200;

    if (!historyDock->isVisible()) {
        historyDock->setFixedHeight(0);
        historyDock->show();

        QPropertyAnimation* anim =                      //logic for history animation dock widget
            new QPropertyAnimation(historyDock, "maximumHeight");
        anim->setDuration(250);
        anim->setStartValue(0);
        anim->setEndValue(h);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        QPropertyAnimation* anim =
            new QPropertyAnimation(historyDock, "maximumHeight");
        anim->setDuration(200);
        anim->setStartValue(historyDock->height());
        anim->setEndValue(0);

        connect(anim, &QPropertyAnimation::finished,
                historyDock, &QWidget::hide);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MainWindow::on_settingsButton_clicked()
{
    QMessageBox::information(this, "Settings",
                             "Settings can be added soon");
}

void MainWindow::on_saveButton_clicked()
{
    if (ui->label->pixmap().isNull()) {
        QMessageBox::warning(this, "Error", "No QR to save");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save QR-Code",
        "",
        "PNG Image (*.png)"
    );

    if (filePath.isEmpty())
        return;

    ui->label->pixmap().save(filePath, "PNG");       //save as button
}


void MainWindow::on_generateButton_clicked()
{
    QString text = ui->textEdit->toPlainText();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "No text to generate");
        return;
    }

    QString filePath =            //create temp file for save qr
        QDir::tempPath() + "/qr_" +
        QString::number(QDateTime::currentMSecsSinceEpoch()) +  //base trick with time if we need different values
        ".png";

    generateQrPng(              //give our inputs in QR generator
        text.toStdString(),
        filePath.toStdString()
    );

    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "Could not generate QR code");
        return;
    }

    ui->label->setPixmap(
        pixmap.scaled(
            ui->label->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation)
    );

    addToHistory(text, filePath);
}


void MainWindow::addToHistory(const QString& name, const QString& path)     //save to history logic
{
    QPixmap icon(path);

    QListWidgetItem* item = new QListWidgetItem(
        QIcon(icon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation)),
        name
    );

    item->setData(Qt::UserRole, path);
    historyList->insertItem(0, item);

    if (historyList->count() > 10)              //max 10 values in history
        delete historyList->takeItem(10);

    saveHistoryToFile();

}

void MainWindow::onHistoryItemClicked(QListWidgetItem* item)
{
    QString path = item->data(Qt::UserRole).toString();
    QPixmap pixmap(path);

    if (pixmap.isNull())
        return;

    ui->label->setPixmap(
        pixmap.scaled(
            ui->label->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation)
    );
}

QString getHistoryFilePath()
{
    QString dir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir().mkpath(dir);

    return dir + "/history.json";
}

void MainWindow::saveHistoryToFile() {
    QJsonArray array;
    for (int i= 0; i<historyList->count(); ++i) {
        QListWidgetItem* item = historyList->item(i);

        QJsonObject obj;
        obj["text"] = item->text();
        obj["filePath"] = item->data(Qt::UserRole).toString();

        array.append(obj);
    }

    QJsonDocument doc(array);

    QFile file(getHistoryFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
}

void MainWindow::loadHistoryFromFile() {
    QFile file(getHistoryFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

if (!doc.isArray()) {
    return;
}
    QJsonArray array = doc.array();

    for (const QJsonValue& val : array) {
        QJsonObject obj = val.toObject();

        QString text = obj["text"].toString();
        QString Path = obj["filePath"].toString();

        if (!QFile::exists(Path)) {
            continue;
        }
        QPixmap icon(Path);
        QListWidgetItem* item = new QListWidgetItem(
           QIcon(icon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation)),text);


        item->setData(Qt::UserRole, Path);
        historyList->insertItem(0, item);
    }

}

void MainWindow::on_decodeButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open QR image",
        "",
        "Images (*.png *.jpg *.jpeg)"
    );

    if (filePath.isEmpty())
        return;

    cv::Mat img = cv::imread(filePath.toStdString());
    if (img.empty()) {
        QMessageBox::warning(this, "Error", "Cannot open image");
        return;
    }

    cv::QRCodeDetector detector;
    std::string decodedText = detector.detectAndDecode(img);

    if (decodedText.empty()) {
        QMessageBox::warning(this, "Result", "QR code not found");
        return;
    }

    // show text in UI
    ui->textEdit->setPlainText(QString::fromStdString(decodedText));

    QMessageBox::information(
        this,
        "QR decoded",
        "QR code successfully decoded"
    );
}
