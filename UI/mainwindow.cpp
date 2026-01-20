#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>

#include "qr_handler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    // ===== Sidebar animation =====
    int topOffset = ui->menuButton->height();
    ui->sideBar->move(-ui->sideBar->width(), topOffset);

    sideBarAnim = new QPropertyAnimation(ui->sideBar, "pos", this);
    sideBarAnim->setDuration(250);
    sideBarAnim->setEasingCurve(QEasingCurve::OutCubic);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_menuButton_clicked()
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

        QPropertyAnimation* anim =
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
    QMessageBox::information(this, "Настройки",
                             "Настройки будут добавлены позже");
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

    ui->label->pixmap().save(filePath, "PNG");
}


void MainWindow::on_generateButton_clicked()
{
    QString text = ui->textEdit->toPlainText();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "No text to generate");
        return;
    }

    QString filePath =
        QDir::tempPath() + "/qr_" +
        QString::number(QDateTime::currentMSecsSinceEpoch()) +
        ".png";

    generateQrPng(
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


void MainWindow::addToHistory(const QString& name, const QString& path)
{
    QPixmap icon(path);

    QListWidgetItem* item = new QListWidgetItem(
        QIcon(icon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation)),
        name
    );

    item->setData(Qt::UserRole, path);
    historyList->insertItem(0, item);

    if (historyList->count() > 10)
        delete historyList->takeItem(10);
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
