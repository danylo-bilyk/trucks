#include "trucks.h"
#include <qdebug.h>
Trucks::Trucks(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    int i=0;
    foreach(QObject*const obj, ui.propertiesVerticalLayout->children()) {
        QWidget* widget = dynamic_cast<QWidget*>(obj);
        qDebug() << ++i;
        if(widget){
            widget->hide();
        }
    }
}

Trucks::~Trucks()
{ }
