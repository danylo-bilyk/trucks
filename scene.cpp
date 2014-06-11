#include <qdebug.h>
#include "scene.h"
#include "link.h"
#include "node.h"
#include "QGraphicsSceneMouseEvent"

namespace   my {
Scene::Scene() : QGraphicsScene(), is_dirty(false), startNode(0), tempLink(0)
{ }

Scene::~Scene()
{ }

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Custom scene mouse down.";
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    qDebug() << "Custom scene mouse up.";
}

Node *Scene::createNode(QPointF pos, NodeType type) {
    is_dirty = true;

    Node    *node = new Node(type);
    node->setPos(pos - Node::getCenter());
    node->setZValue(1000.0);

    addItem(node);

    return (node);
}

bool Scene::isDirty() const {
    return (is_dirty);
}

Link *Scene::createLink(Node *startNode, Node *endNode) {
    is_dirty = true;

    Link    *link = new Link(startNode, endNode);
    link->setZValue(0.0);

    addItem(link);

    return (link);
}

Link *Scene::endLinkCreation(QGraphicsItem *obj) {
    Node    *endNode = dynamic_cast<NodePtr> (obj);

    tempLink->setEnd(endNode);

    Link    *link = tempLink;
    tempLink = 0;

    cancelLinkCreation();
    return (link);
}

void Scene::cancelLinkCreation() {
    startNode = 0;

    if (tempLink) {
        this->removeItem(tempLink);
        delete tempLink;
        tempLink = 0;
    }

    if (tempNode) {
        this->removeItem(tempNode);
        delete tempNode;
        tempNode = 0;
    }
}

LinkPtr Scene::createDoubleLink(Node *startNode, Node *endNode)
{
    is_dirty = true;

    Link    *link = new Link(startNode, endNode, Link::DOUBLE_LINK);
    link->setZValue(0.0);

    addItem(link);

    return (link);
}

void Scene::startLinkCreation(QGraphicsItem *obj, QPointF pt) {
    startNode = dynamic_cast<NodePtr> (obj);

    tempNode = createNode(pt, STORAGE);
    tempNode->setVisible(false);
    tempNode->setZValue(0);

    tempLink = createLink(startNode, tempNode);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    QPointF pos = e->scenePos();

    if (tempLink && tempNode) {
        tempNode->setPos(pos - Node::getCenter());
    } else {
        QGraphicsScene::mouseMoveEvent(e);
    }
}
}
