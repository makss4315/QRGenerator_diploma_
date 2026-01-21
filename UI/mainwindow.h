#pragma once

#include <QMainWindow>
#include  <QDockWidget>
#include <QListWidget>
#include <QPropertyAnimation>
#include <QStringList>




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

        void on_decodeButton_clicked();

        void on_settingsButton_clicked();

        void on_historyButton_clicked();

        void onHistoryItemClicked(QListWidgetItem* item);

        void saveHistoryToFile();

        void loadHistoryFromFile();



private:
    QPropertyAnimation* sideBarAnim;
    QDockWidget* historyDock;
    QListWidget* historyList;

    void addToHistory(const QString& name, const QString& path);

    Ui::MainWindow *ui;
};
