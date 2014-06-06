#include "trucks.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>

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


    QGraphicsPixmapItem* item1 = new QGraphicsPixmapItem(QPixmap(":/images/Resources/table.png"));
    QGraphicsScene* scene = new QGraphicsScene();
    ui.graphicsView_3->setScene(scene);
    scene->addItem(item1);

    QGraphicsPixmapItem* item2= new QGraphicsPixmapItem(QPixmap(":/images/Resources/DispDiagr.png"));
    QGraphicsScene* scene1 = new QGraphicsScene();
    ui.graphicsView->setScene(scene1);
    scene1->addItem(item2);

    QGraphicsPixmapItem* item3 = new QGraphicsPixmapItem(QPixmap(":/images/Resources/Gantt.png"));
    QGraphicsScene* scene2 = new QGraphicsScene();
    ui.graphicsView_2->setScene(scene2);
    scene2->addItem(item3);
}

Trucks::~Trucks()
{ }
