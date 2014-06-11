#include <QGraphicsScene>
#include <QtGui>
#include "link.h"

namespace   my {
Link::Link(Node *node1, Node *node2, LinkType linkType /*= SINGLE_LINK*/)
    : QGraphicsLineItem(), from(node1), to(node2), type(linkType), draft(true)
{
    if (from == to || !node1 || !node2) {
        throw Link::WrongNode();
    } else {
        setBegin(node1);
        setEnd(node2);
    }

    pen = new QPen();
    pen2 = new QPen();

    setFlag(ItemIsSelectable);

    setAcceptHoverEvents(true);



    pen2->setWidth(12);
    pen2->setColor(Qt::black);

    if (type == SINGLE_LINK) {
        pen->setWidth(5);

        setPen(*pen);

        pen->setStyle(Qt::SolidLine);
        pen2->setStyle(Qt::NoPen);
    } else {
        setPen(*pen2);

        pen->setWidth(2);

        pen->setStyle(Qt::DashLine);
        pen2->setStyle(Qt::SolidLine);
    }
}

Link::~Link() {
    delete pen;
    delete pen2;
}

void Link::setupMajorPenColor()
{
    if (type == SINGLE_LINK) {
        if (isSelected()) {
            pen->setColor(Qt::red);
        } else {
            pen->setColor(Qt::black);
        }
    } else {
        if (isSelected()) {
            pen->setColor(Qt::yellow);
        } else {
            pen->setColor(Qt::white);
        }
    }
}

void Link::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);

    setupMajorPenColor();

    const QPointF   &nodeCenterOffset = Node::getCenter();
    float           radius = (QLineF(0, 0, nodeCenterOffset.x(), 0).length());

    QPointF         start = from->pos() + nodeCenterOffset;
    QPointF         end = to->pos() + nodeCenterOffset;

    QLineF          centerLine(start, end);

    QLineF          normal = centerLine;

    normal.setLength(radius);

    QPointF det(normal.dx(), normal.dy());

    QPointF fromOuter = start + det;
    QPointF toOuter = end;

    if (draft) {
        toOuter -= det;
    }

    QLineF  outerLine(fromOuter, toOuter);
    setLine(centerLine);
    setLine(outerLine);

    if (from->collidesWithItem(to) || centerLine.length() < 2 * radius) {
        return;
    }

    painter->setPen(*pen2);
    painter->drawLine(line());


    painter->setPen(*pen);
    painter->drawLine(line());
}

void Link::setBegin(Node *node, bool create) {
    if (to == node || !node) {
        throw Link::WrongNode();
    }

    if (from) {
        from->unbind(this);
    }

    from = node;
    from->bind(this);

    draft = !create;
}

void Link::setEnd(Node *node, bool create) {
    if (from == node || !node) {
        throw Link::WrongNode();
    }

    if (to) {
        to->unbind(this);
    }

    to = node;
    to->bind(this);

    draft = !create;
}

void Link::unbind() {
    if (to) {
        to->unbind(this);
    }

    if (from) {
        from->unbind(this);
    }
}
}
