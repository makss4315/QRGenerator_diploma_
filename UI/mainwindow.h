#pragma once

#include <QMainWindow>
#include  <QDockWidget>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        void on_generateButton_clicked();

        void on_saveButton_clicked();

        void on_menuButton_clicked();

        void on_historyButton_clicked();

        void on_settingsButton_clicked();



private:
    Ui::MainWindow *ui;
};
