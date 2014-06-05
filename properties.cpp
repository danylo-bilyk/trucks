#include <QHeaderView>

#include "properties.h"
#include "node.h"

Properties::Properties(QWidget *parent)
    : QTableView(parent) {

}

Properties::~Properties() {

}

void Properties::updateModel( QAbstractTableModel *model ) {
    this->verticalHeader()->show();
    QTableView::setModel(model);
}
