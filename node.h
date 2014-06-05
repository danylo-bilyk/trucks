#ifndef NODE_H
#define NODE_H

#include "common.h"

#include <QGraphicsPixmapItem>
#include <QAbstractItemModel>
#include <QItemDelegate>

namespace   my {
class TruckBoxDelegate : public QItemDelegate {
        Q_OBJECT

    public:
        TruckBoxDelegate(QObject *parent = 0);

        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

        void    setEditorData(QWidget *editor, const QModelIndex &index) const;
        void    setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

        void    updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class NodeModel : public QAbstractTableModel {
        Q_OBJECT

    public:
        NodeModel(QObject *parent);
        int                         rowCount(const QModelIndex &parent = QModelIndex()) const;
        int                         columnCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant                    data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        virtual QVariant            headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        Qt::ItemFlags               flags(const QModelIndex &index) const;
        bool                        setData(const QModelIndex &index, const QVariant &value, int role);

        virtual QMap<int, QVariant> itemData(const QModelIndex &index) const;

    private:
        QString             name;
        NodeType            type;
        size_t              trucks;

        static const int    Custom_Item_Role = Qt::UserRole + 1;

        static const int    getItemRole() {
            return Custom_Item_Role;
        }
};

class Node : public QGraphicsPixmapItem {

    protected:
        static const size_t diameter = 48;
        QStringList         stringList;

    public:
        static const QPointF    &getCenter();

        Node(NodeType);
        ~                       Node();

        QRectF                  boundingRect() const;
        void                    paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

        QAbstractTableModel     *getModel();

        LinksArray              links()     { return (links_); }

        void                    bind(LinkPtr link);
        void                    unbind(LinkPtr link);

    protected:
        NodeModel       *myModel;

        bool            isHovered() const;

        void            mousePressEvent(QGraphicsSceneMouseEvent *);
        void            mouseReleaseEvent(QGraphicsSceneMouseEvent *);
        void            hoverEnterEvent(QGraphicsSceneHoverEvent *);
        void            hoverLeaveEvent(QGraphicsSceneHoverEvent *);

        QPainterPath    shape() const;

        QString         getImageName();
        void            loadPicture();

        void            paintBackground(QPainter *painter);
        void            paintForegroundOverlay(QPainter *painter);

        void            initDrawingTools();
        void            setBgTools();
        void            setFgTools();

    private:
        LinksArray  links_;

        bool        is_hovered;

        QBrush      *bgBrush;
        QBrush      *fgBrush;
        QPen        *bgPen;
        QPen        *fgPen;

        NodeType    type;

        #pragma region Graphics elements

    protected:
        // Distances
        static const size_t             radius = diameter / 2;

        static const size_t             picturePadding = 5;

        static const size_t             outerCirclePenWidth = 2;
        static const size_t             innerCirclePenWidth = 2;
        static const size_t             innerCirclePadding = 6;
        static const size_t             innerCircleRadius = radius - innerCirclePadding;

        // Normal
        static const Qt::BrushStyle     normalBgBrushStyle = Qt::SolidPattern;
        static const Qt::GlobalColor    normalBgBrushColor = Qt::white;

        static const Qt::BrushStyle     normalFgBrushStyle = Qt::NoBrush;
        static const Qt::GlobalColor    normalFgBrushColor = Qt::white;

        static const Qt::PenStyle       normalBgPenStyle = Qt::NoPen;
        static const Qt::GlobalColor    normalBgPenColor = Qt::black;

        static const Qt::PenStyle       normalFgPenStyle = Qt::SolidLine;
        static const Qt::GlobalColor    normalFgPenColor = Qt::black;

        // Hovered
        static const Qt::BrushStyle     hoverBgBrushStyle = Qt::SolidPattern;
        static const Qt::GlobalColor    hoverBgBrushColor = Qt::yellow;

        static const Qt::BrushStyle     hoverFgBrushStyle = Qt::Dense2Pattern;
        static const QColor             hoverFgBrushColor;

        static const Qt::PenStyle       hoverBgPenStyle = Qt::SolidLine;
        static const Qt::GlobalColor    hoverBgPenColor = Qt::black;

        static const Qt::PenStyle       hoverFgPenStyle = Qt::SolidLine;
        static const Qt::GlobalColor    hoverFgPenColor = Qt::black;

        // Selected
        static const Qt::BrushStyle     selectedBgBrushStyle = Qt::SolidPattern;
        static const Qt::GlobalColor    selectedBgBrushColor = Qt::red;

        static const Qt::BrushStyle     selectedFgBrushStyle = Qt::NoBrush;
        static const Qt::GlobalColor    selectedFgBrushColor = Qt::yellow;

        static const Qt::PenStyle       selectedBgPenStyle = Qt::SolidLine;
        static const Qt::GlobalColor    selectedBgPenColor = Qt::black;

        static const Qt::PenStyle       selectedFgPenStyle = Qt::SolidLine;
        static const Qt::GlobalColor    selectedFgPenColor = Qt::black;

        static QPointF                  centerOffset;

        #pragma endregion
};
}

#endif // NODE_H
