#include "node.h"

#include <QDebug>
#include <QtGui>
#include <QColor>
#include <QStringList>
#include <QSpinBox>
#include <vector>

using namespace std;

namespace       my {
QPointF Node::      centerOffset(Node::radius, Node::radius);

const QColor Node:: hoverFgBrushColor = QColor(128, 128, 255, 128);

Node::Node(NodeType nodeType) : QGraphicsPixmapItem(), is_hovered(false), type(nodeType) {
    myModel = new NodeModel(0);
    stringList.append("TEST1");
    stringList.append("TEST2");
    stringList.append("TEST3");
    stringList.append("TEST4");
    stringList.append("TEST5");

    initDrawingTools();
    loadPicture();
    setAcceptHoverEvents(true);

    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}

Node::~Node() {
    delete myModel;

    delete bgBrush;
    delete fgBrush;
    delete bgPen;
    delete fgPen;
}

void Node::paintForegroundOverlay(QPainter *painter) {
    setFgTools();

    fgPen->setWidth(innerCirclePenWidth);

    painter->setBrush(*fgBrush);
    painter->setPen(*fgPen);

    painter->drawEllipse(getCenter(), innerCircleRadius, innerCircleRadius);

    size_t  width = outerCirclePenWidth;

    fgBrush->setStyle(Qt::NoBrush);
    fgPen->setWidth(width);

    painter->setBrush(*fgBrush);
    painter->setPen(*fgPen);

    width /= 2;
    painter->drawEllipse(getCenter(), radius - width, radius - width);
}

void Node::paintBackground(QPainter *painter) {
    setBgTools();

    size_t  width = outerCirclePenWidth;

    bgPen->setWidth(width);

    painter->setBrush(*bgBrush);
    painter->setPen(*bgPen);

    width /= 2;
    painter->drawEllipse(getCenter(), radius - width, radius - width);

    bgPen->setWidth(innerCirclePenWidth);
    bgBrush->setColor(Qt::white);

    painter->setBrush(*bgBrush);
    painter->setPen(*bgPen);

    painter->drawEllipse(getCenter(), innerCircleRadius, innerCircleRadius);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    paintBackground(painter);

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    QGraphicsPixmapItem::paint(painter, item, widget);

    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    paintForegroundOverlay(painter);
}

void Node::loadPicture() {
    QPixmap         pix(getImageName());

    const size_t    offset = 0; //picturePadding;
    qDebug() << pix.width() << "x" << pix.height();

    setPixmap(pix.scaled(QSize(diameter + offset, diameter + offset)));

    setFlags(QGraphicsPixmapItem::flags() | QGraphicsItem::ItemClipsToShape);
}

void Node::initDrawingTools() {
    bgBrush = new QBrush();
    fgBrush = new QBrush();
    bgPen = new QPen();
    fgPen = new QPen();
    setFgTools();
    setBgTools();
}

void Node::setBgTools() {
    if (isSelected()) {
        bgBrush->setColor(selectedBgBrushColor);
        bgBrush->setStyle(selectedBgBrushStyle);

        bgPen->setColor(selectedBgPenColor);
        bgPen->setStyle(selectedBgPenStyle);
    } else if (isHovered()) {
        bgBrush->setColor(hoverBgBrushColor);
        bgBrush->setStyle(hoverBgBrushStyle);

        bgPen->setColor(hoverBgPenColor);
        bgPen->setStyle(hoverBgPenStyle);
    } else {
        bgBrush->setColor(normalBgBrushColor);
        bgBrush->setStyle(normalBgBrushStyle);

        bgPen->setColor(normalBgPenColor);
        bgPen->setStyle(normalBgPenStyle);
    }
}

void Node::setFgTools() {
    if (isSelected()) {
        fgBrush->setColor(selectedFgBrushColor);
        fgBrush->setStyle(selectedFgBrushStyle);

        fgPen->setColor(selectedFgPenColor);
        fgPen->setStyle(selectedFgPenStyle);
    } else if (isHovered()) {
        fgBrush->setColor(hoverFgBrushColor);
        fgBrush->setStyle(hoverFgBrushStyle);

        fgPen->setColor(hoverFgPenColor);
        fgPen->setStyle(hoverFgPenStyle);
    } else {
        fgBrush->setColor(normalFgBrushColor);
        fgBrush->setStyle(normalFgBrushStyle);

        fgPen->setColor(normalFgPenColor);
        fgPen->setStyle(normalFgPenStyle);
    }
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Custom item mouse down.";
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Custom item mouse up.";
    QGraphicsItem::mouseReleaseEvent(event);
}

QString Node::getImageName() {
    QString         filename;
    const QString   path = ":/images/Resources/images/";

    switch (type) {
        case STORAGE:
            filename = "dump.png";
            break;

        case INTERCHANGE:
            filename = "circle-outline-64.png";
            break;

        case MINEDUMP:
            filename = "mine.png";
            break;

        default:
            throw std::exception();
    }

    return (path + filename);
}

QRectF Node::boundingRect() const {
    return (*(new QRectF(0, 0, diameter, diameter)));
}

QPainterPath Node::shape() const {
    QPainterPath    path;
    path.addEllipse(boundingRect());
    return (path);
}

bool Node::isHovered() const {
    return (is_hovered);
}

const QPointF &Node::getCenter() {
    return (centerOffset);
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    is_hovered = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    is_hovered = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

QAbstractTableModel *Node::getModel() {
    return (myModel);
}

void Node::bind(LinkPtr link) {
    LinksArray::iterator    it;
    bool                    found = false;

    for (it = links_.begin(); it != links_.end(); ++it) {
        if (link == *it) {
            found = true;
        }
    }

    if (!found) {
        links_.push_back(link);
    }
}

void Node::unbind(LinkPtr link) {
    LinksArray::iterator    it;

    for (it = links_.begin(); it != links_.end();) {
        bool    erased = false;

        if (link == *it) {
            it = links_.erase(it);
            erased = true;
        }

        if (!erased) {
            ++it;
        }
    }
}

//////////////////////////////////////////////////////////////////////////

const int NodeModel::Custom_Item_Role  = Qt::UserRole + 1;

NodeModel::NodeModel(QObject *parent) : QAbstractTableModel(parent)
{ }

int NodeModel::rowCount(const QModelIndex & /*parent*/ ) const {
    return (3);
}

int NodeModel::columnCount(const QModelIndex & /*parent*/ ) const {
    return (1);
}

QVariant NodeModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.row()) {
            case 0:
                return (name);

            case 1:
                return QString::number(type);

            case 2:
                return QString::number(trucks);

            default:
                return (QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() + 1));
        }
    }

    return (QVariant());
}

QVariant NodeModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return (QString("Values"));

            }
        } else {
            switch (section) {
                case 0:
                    return (QString("Name"));

                case 1:
                    return (QString("Type"));

                case 2:
                    return (QString("Trucks"));
            }
        }
    }

    return (QVariant());
}

bool NodeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        switch (index.row()) {
            case 0:
                name = value.toString();
        }
    }

    return (true);
}

Qt::ItemFlags NodeModel::flags(const QModelIndex &index) const {
    return (Qt::ItemIsEditable | QAbstractTableModel::flags(index));
}

QMap<int, QVariant> NodeModel::itemData(const QModelIndex &index) const {
    QMap<int, QVariant> result;

    //QVector<QStandardItemData>::const_iterator it;
    //for (it = values.begin(); it != values.end(); ++it)
    //{ result.insert((*it).role, (*it).value); }
    //return result;
    QMap<int, QVariant> m = QAbstractItemModel::itemData(index);
    m[NodeModel::Custom_Item_Role] = data(index, NodeModel::Custom_Item_Role);
    return (m);
}

//////////////////////////////////////////////////////////////////////////
TruckBoxDelegate::TruckBoxDelegate(QObject *parent /*= 0*/ ) : QItemDelegate(parent)
{ }

QWidget *TruckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const {
    QSpinBox    *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);
    return (editor);
}

void TruckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    int         value = index.model()->data(index, Qt::EditRole).toInt();

    QSpinBox    *spinBox = dynamic_cast<QSpinBox *>(editor);
    spinBox->setValue(value);
}

void TruckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QSpinBox    *spinBox = dynamic_cast<QSpinBox *>(editor);
    spinBox->interpretText();

    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}

void TruckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const {
    editor->setGeometry(option.rect);
}

}
