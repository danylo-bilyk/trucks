#ifndef TRUCKS_H
#define TRUCKS_H

#include <QtWidgets/QMainWindow>
#include "ui_trucks.h"

class Trucks : public QMainWindow {
        Q_OBJECT

    public:
        Trucks(QWidget *parent = 0);
        ~   Trucks();
    private:
        Ui::MainWindow ui;
};
#endif // TRUCKS_H
