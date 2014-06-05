#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QTableView>

class Properties : public QTableView {
        Q_OBJECT

    public Q_SLOTS:
        void updateModel(QAbstractTableModel *model);

    public:
        Properties(QWidget *parent);
        ~   Properties();

    private:
};
#endif // PROPERTIES_H
