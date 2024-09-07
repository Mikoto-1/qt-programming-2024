//
// Created by hp on 24-8-30.
//

#include "Platform.h"

Platform::Platform(QGraphicsItem* parent, const QString& pixmapPath): Item(parent, pixmapPath)
{
    setScale(5);
    // pixmapItem->setScale(5);
    topEllipseItem = new QGraphicsEllipseItem(-1 + Item::boundingRect().width() / 2, -1, 2, 2, this);
    topEllipseItem->setBrush(Qt::red);
    topEllipseItem->setZValue(1);

    bottomEllipseItem = new QGraphicsEllipseItem(-1 + Item::boundingRect().width() / 2,
                                                 -1 + Item::boundingRect().height(), 2, 2, this);
    bottomEllipseItem->setBrush(Qt::red);
    bottomEllipseItem->setZValue(1);

    leftEllipseItem = new QGraphicsEllipseItem(-1, -1 + Item::boundingRect().height() / 2, 2, 2, this);
    leftEllipseItem->setBrush(Qt::red);
    leftEllipseItem->setZValue(1);

    rightEllipseItem = new QGraphicsEllipseItem(-1 + Item::boundingRect().width(),
                                                -1 + Item::boundingRect().height() / 2, 2, 2, this);
    rightEllipseItem->setBrush(Qt::red);
    rightEllipseItem->setZValue(1);
}

qreal Platform::getHeight() const
{
    return scale * pixmapItem->boundingRect().height();
}

qreal Platform::getWidth() const
{
    return scale * pixmapItem->boundingRect().width();
}

qreal Platform::getLeftBorder() const
{
    return pos().x();
}

qreal Platform::getRightBorder() const
{
    return pos().x() + scale * pixmapItem->boundingRect().width();
}

qreal Platform::getTopBorder() const
{
    return pos().y();
}

qreal Platform::getBottomBorder() const
{
    return pos().y() + scale * pixmapItem->boundingRect().height();
}
