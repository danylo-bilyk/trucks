#ifndef SCENE_H
#define SCENE_H

#include "common.h"

#include <QGraphicsScene>

namespace   my {
class Scene : public QGraphicsScene {
        Q_OBJECT

    public:
        Scene();
        ~       Scene();

        NodePtr createNode(QPointF pos, NodeType type);

        bool    isDirty() const;

        void    startLinkCreation(QGraphicsItem *obj, QPointF pt);
        void    cancelLinkCreation();
        LinkPtr endLinkCreation(QGraphicsItem *obj);

        LinkPtr         createLink(Node *startNode, Node *endNode);
        LinkPtr         createDoubleLink(Node *startNode, Node *endNode);
    protected:


        virtual void    mousePressEvent(QGraphicsSceneMouseEvent *event);
        virtual void    mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        virtual void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    private:
        bool    is_dirty;

        NodePtr startNode;
        NodePtr tempNode;
        LinkPtr tempLink;
};
}

#endif // SCENE_H
