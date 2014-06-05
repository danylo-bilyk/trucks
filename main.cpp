#include "trucks.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
    QApplication    a( argc, argv );
    Trucks          w;
    w.show();
    return ( a.exec() );
}
