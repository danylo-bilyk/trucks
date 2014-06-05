#ifndef LINK_H
#define LINK_H

#include <QGraphicsLineItem>
#include "node.h"

namespace   my {
class Link : public QGraphicsLineItem {

    public:
        Link(NodePtr, NodePtr);
        ~       Link();

        void    setBegin(NodePtr node, bool create = true);
        void    setEnd(NodePtr node, bool create = true);

        void    paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

        void    unbind();

    private:
        NodePtr from;
        NodePtr to;

        QPen    *pen;
        bool    draft;

    public:
        class WrongNode : public std::exception
        { };
};
}

#endif // LINK_H
