#include "common.h"

#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QMessageBox>

#include "node.h"
#include "view.h"
#include "scene.h"
#include "link.h"

using namespace my;

TrucksGraphicView::TrucksGraphicView(QWidget *parent) : QGraphicsView(parent), mode(MODE_SELECT) {
    initScene();
    setRenderHint(QPainter::Antialiasing);
}

TrucksGraphicView::~TrucksGraphicView() {
    freeScene();
}

void TrucksGraphicView::toggleSelectMode(bool toggled) {
    toggleMode(MODE_SELECT, toggled);
}

void TrucksGraphicView::toggleStorageAddMode(bool toggled) {
    toggleMode(MODE_STORAGE_ADD, toggled);
}

void TrucksGraphicView::toggleRoadAddMode(bool toggled) {
    toggleMode(MODE_ROAD_ADD, toggled);
}

void TrucksGraphicView::toggleMode(EditMode targetMode, bool toggled) {
    if (toggled) {
        if (mode != targetMode) {
            mode = targetMode;

            emit    selectModeToggled(mode == MODE_SELECT);
            emit    storageAddModeToggled(mode == MODE_STORAGE_ADD);
            emit    mineDumpAddModeToggled(mode == MODE_MINEDUMP_ADD);
            emit    interchangeAddModeToggled(mode == MODE_INTERCHANGE_ADD);
            emit    roadAddModeToggled(mode == MODE_ROAD_ADD);
            emit    doubleRoadAddModeToggled(mode == MODE_DOUBLEROAD_ADD);
            qDebug() << "Mode enabled:" << mode;
        }
    } else {
        if (mode == targetMode) {
            qDebug() << "Mode disabled:" << mode;

            if (mode != DEFAULT_MODE) {
                toggleMode(DEFAULT_MODE);
            }
        }
    }
}

void TrucksGraphicView::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Custom view mouse down.";

    QPointF         pt = mapToScene(event->pos());
    QGraphicsItem   *obj = itemAt(event->pos());

    switch (mode) {
        case MODE_STORAGE_ADD: {
                scene->createNode(pt, STORAGE);
                toggleMode(DEFAULT_MODE);
            }

            break;

        case MODE_INTERCHANGE_ADD: {
                scene->createNode(pt, INTERCHANGE);
                toggleMode(DEFAULT_MODE);
            }

            break;

        case MODE_MINEDUMP_ADD: {
                scene->createNode(pt, MINEDUMP);
                toggleMode(DEFAULT_MODE);
            }

            break;

        case MODE_ROAD_ADD: {
                if (event->button() != Qt::LeftButton) {
                    break;
                }

                linkStart = dynamic_cast<NodePtr> (obj);

                if (linkStart) {
                    qDebug() << "Started link creation process";
                    scene->startLinkCreation(obj, pt);
                } else {
                    toggleMode(DEFAULT_MODE);
                }
            }

            break;

        case DEFAULT_MODE: {
                selectedObject = obj;

                NodePtr node = dynamic_cast<NodePtr> (selectedObject);

                if (node) {
                    emit    selectionChanged(node->getModel());
                } else {
                    selectedObject = 0;
                }
            }   /* no break */

        default:
            QGraphicsView::mousePressEvent(event);
    }
}

void TrucksGraphicView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsItem   *obj = itemAt(event->pos());

    switch (mode) {
        case MODE_ROAD_ADD: {
                if (event->button() != Qt::LeftButton) {
                    break;
                }

                linkEnd = dynamic_cast<NodePtr> (obj);

                if ((linkStart && linkEnd) && (linkEnd != linkStart)) {
                    scene->endLinkCreation(obj);
                    qDebug() << "Finished link creation process";
                } else {
                    scene->cancelLinkCreation();
                    qDebug() << "Canceled link creation process";
                }

                linkStart = linkEnd = 0;
            }

            break;

        default: {
            qDebug() << "WARNING" << __FILE__ << __LINE__ << endl;
        }
    }

    QGraphicsView::mouseReleaseEvent(event);
    qDebug() << "Custom view mouse release.";
}

void TrucksGraphicView::triggerClearScene() {
    QMessageBox::StandardButton reply = QMessageBox::No;
    const QString               title = ("Question");
    const QString               text = ("Clear scene?");

    if (scene->isDirty()) {
        reply = QMessageBox::question(this, title, text);
    }

    if (reply == QMessageBox::Yes || !scene->isDirty()) {
        clearScene();
    }
}

void TrucksGraphicView::clearScene() {
    qDebug() << "Clearing scene";
    scene->clear();
}

void TrucksGraphicView::toggleInterchangeAddMode(bool toggle) {
    toggleMode(MODE_INTERCHANGE_ADD, toggle);
}

void TrucksGraphicView::toggleMineDumpAddMode(bool toggle) {
    toggleMode(MODE_MINEDUMP_ADD, toggle);
}

void TrucksGraphicView::toggleDoubleRoadAddMode(bool toggle) {
    toggleMode(MODE_DOUBLEROAD_ADD, toggle);
}

void TrucksGraphicView::initScene() {
    scene = new Scene();
    setScene(scene);
    scene->setSceneRect(0, 0, 525, 375);

    NodePtr pn1 = scene->createNode(QPoint(-100, 250), MINEDUMP);

    NodePtr m1 = scene->createNode(QPoint(-100,150), INTERCHANGE);
    NodePtr m2 = scene->createNode(QPoint(-100,50), INTERCHANGE);
    NodePtr m3 = scene->createNode(QPoint(100,50), INTERCHANGE);
    NodePtr m4 = scene->createNode(QPoint(350, 50), INTERCHANGE);
    NodePtr m5 = scene->createNode(QPoint(525, 75), INTERCHANGE);
    NodePtr m6 = scene->createNode(QPoint(500, 200), INTERCHANGE);
    NodePtr m7 = scene->createNode(QPoint(300, 125), INTERCHANGE);
    NodePtr m8 = scene->createNode(QPoint(400, 200), INTERCHANGE);
    NodePtr m9 = scene->createNode(QPoint(500, 275), INTERCHANGE);
    NodePtr m10 = scene->createNode(QPoint(300, 275), INTERCHANGE);
    NodePtr m11 = scene->createNode(QPoint(150, 275), INTERCHANGE);

    NodePtr pr0 = scene->createNode(QPoint(225, 200), STORAGE);
    NodePtr pr1 = scene->createNode(QPoint(75, 200), STORAGE);
    NodePtr pr2 = scene->createNode(QPoint(650, 200), STORAGE);

    scene->createLink(m1, m2);
    scene->createLink(m2, m3);
    scene->createLink(m3, m4);

    scene->createDoubleLink(pn1, m1);

    scene->createDoubleLink(pr0, m10);
    scene->createDoubleLink(pr1, m11);
    scene->createDoubleLink(pr2, m5);
    scene->createDoubleLink(pr2, m6);
    scene->createDoubleLink(pr2, m9);

    scene->createDoubleLink(m4, m5);
    scene->createDoubleLink(m4, m7);

    scene->createDoubleLink(m6, m5);
    scene->createDoubleLink(m6, m8);
    scene->createDoubleLink(m6, m9);

    scene->createLink(m7, m8);
    scene->createDoubleLink(m7, m10);

    scene->createDoubleLink(m10, m8);
    scene->createDoubleLink(m10, m9);
    scene->createDoubleLink(m10, m11);
}

void TrucksGraphicView::freeScene() {
    delete scene;
}

void TrucksGraphicView::triggerDeleteSelection() {
    if (selectedObject) {
        LinkPtr link = dynamic_cast<LinkPtr>(selectedObject);
        NodePtr node = dynamic_cast<NodePtr>(selectedObject);

        if (link) {
            link->unbind();
        }

        if (node) {
            LinksArray              links = node->links();
            LinksArray::iterator    it;

            for (it = links.begin(); it != links.end(); ++it) {
                LinkPtr link = *it;
                link->unbind();
                scene->removeItem(link);
            }
        }

        scene->removeItem(selectedObject);
        delete selectedObject;
    }
}
