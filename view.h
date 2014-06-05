#ifndef TRUCKSGRAPHICVIEW_H
#define TRUCKSGRAPHICVIEW_H

#include "common.h"
#include <QGraphicsView>
#include <QAbstractItemModel>

class TrucksGraphicView : public QGraphicsView {
        Q_OBJECT

    public:
        TrucksGraphicView(QWidget *parent);
        ~   TrucksGraphicView();

        enum EditMode {
            MODE_SELECT,
            MODE_STORAGE_ADD,
            MODE_INTERCHANGE_ADD,
            MODE_MINEDUMP_ADD,
            MODE_ROAD_ADD,
            MODE_DOUBLEROAD_ADD
        };

        void switchToMode(EditMode newMode = MODE_SELECT);

        public
        Q_SLOTS
    :
        void toggleSelectMode(bool toggle = true);

        void    toggleStorageAddMode(bool toggle = true);
        void    toggleMineDumpAddMode(bool toggle = true);
        void    toggleInterchangeAddMode(bool toggle = true);

        void    toggleRoadAddMode(bool toggle = true);
        void    toggleDoubleRoadAddMode(bool toggle = true);

        void    triggerClearScene();
        void    triggerDeleteSelection();

    protected:
        void    mousePressEvent(QMouseEvent *event);
        void    mouseReleaseEvent(QMouseEvent *event);

        void    initScene();
        void    freeScene();

    private:
        void                    toggleMode(EditMode targetMode, bool toggled = true);
        void                    clearScene();

        const static EditMode   DEFAULT_MODE = MODE_SELECT;

        EditMode                mode;

        my::Scene *scene;

        my::Node *linkStart;
        my::Node *linkEnd;

        QGraphicsItem   *selectedObject;

    Q_SIGNALS:
        void    selectModeToggled(bool toggled = true);

        void    storageAddModeToggled(bool toggled = true);
        void    interchangeAddModeToggled(bool toggled = true);
        void    mineDumpAddModeToggled(bool toggled = true);

        void    roadAddModeToggled(bool toggled = true);
        void    doubleRoadAddModeToggled(bool toggled = true);

        void    selectionChanged(QAbstractTableModel *model);
};
#endif // TRUCKSGRAPHICVIEW_H
