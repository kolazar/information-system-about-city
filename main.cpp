#include "mainwindow.h"
#include <QApplication>
#include "type.h"

static city* root = NULL;

city* getRoot()
{
    return root;
}

void setRoot(city* r)
{
    root = r;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
