#ifndef TRUCKS_H
#define TRUCKS_H

#include <QtWidgets/QMainWindow>
#include "ui_trucks.h"

class Trucks : public QMainWindow {
        Q_OBJECT

    public:
        Trucks(QWidget *parent = 0);
        ~   Trucks();

        void showEvent(QShowEvent *e)
        {
            QMainWindow::showEvent(e);
            static bool firstStart = true;
            if (firstStart)
            {
                emit startJob();
                firstStart = false;
            }
        }

    Q_SIGNALS:

        void    startJob();

    private:
        Ui::MainWindow ui;
};
#endif // TRUCKS_H
