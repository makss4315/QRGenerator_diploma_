#include <QApplication>
#include "mainwindow.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);



    QFile styleFile("style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        app.setStyleSheet(stream.readAll());
        styleFile.close();
    }

 MainWindow w;
    w.show();

    return app.exec();
}
