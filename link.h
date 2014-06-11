#ifndef LINK_H
#define LINK_H

#include <QGraphicsLineItem>
#include "node.h"

namespace   my {
class Link : public QGraphicsLineItem {

    public:
        typedef enum {SINGLE_LINK, DOUBLE_LINK} LinkType;

        Link(NodePtr, NodePtr, LinkType linkType = SINGLE_LINK);
        ~       Link();

        void    setBegin(NodePtr node, bool create = true);
        void    setEnd(NodePtr node, bool create = true);

        void    paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

        void    unbind();

    private:
        NodePtr from;
        NodePtr to;

        LinkType type;

        QPen    *pen;
        QPen    *pen2;

        bool    draft;

    public:
        class WrongNode : public std::exception
        { };
        void setupMajorPenColor();
};
}

#endif // LINK_H
