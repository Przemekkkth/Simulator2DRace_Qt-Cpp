#ifndef QUAD_H
#define QUAD_H

#include <QGraphicsScene>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

struct Quad
{
    void drawQuad(QGraphicsScene *_scene, QColor c, int x1,int y1,int w1,int x2,int y2,int w2)
    {
        QPolygonF shape;
        shape.append(QPointF(x1-w1, y1));
        shape.append(QPointF(x2-w2, y2));
        shape.append(QPointF(x2+w2, y2));
        shape.append(QPointF(x1+w1, y1));

        QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(shape);
        polygonItem->setBrush(QBrush(c));
        polygonItem->setPen(QPen(c));
        _scene->addItem(polygonItem);
    }
};

#endif // QUAD_H
