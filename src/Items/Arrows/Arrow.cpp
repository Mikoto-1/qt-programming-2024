//
// Created by hp on 24-9-2.
//

#include "Arrow.h"

Arrow::Arrow(QGraphicsItem* parent, const QString& pixmapPath) : Weapon(parent, pixmapPath)
{
    pixmapItem->setPos(-50, -90);
    set_damage(4);
}

void Arrow::mountToParent()
{
    Weapon::mountToParent();
    setTransform(QTransform().scale(1,1));
    setPos(-90,-120);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -90);
        qDebug() << pos().x() << "" << pos().y() << pixmapItem->pos().x() << "" << pixmapItem->pos().y();
    }
    setZValue(2);
}

void Arrow::unmount()
{
    Weapon::unmount();
}

void Arrow::equippedToParent()
{
    Weapon::equippedToParent();
    mountToParent();
}

void Arrow::unequippedFromParent()
{
    Weapon::unequippedFromParent();
    setTransform(QTransform().scale(-1,1));
    setPos(25,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -100);
    }
    setZValue(-1);
}

QString Arrow::getType()
{
    return "";
}
