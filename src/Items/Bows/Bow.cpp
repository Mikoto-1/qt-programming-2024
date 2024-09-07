//
// Created by hp on 24-8-31.
//

#include "Bow.h"

#include "../Effects/FireEffect.h"
#include "../Effects/LightningEffect.h"

Bow::Bow(QGraphicsItem* parent, const QString& pixmapPath) : Weapon(parent, pixmapPath), initialVelocity(0),
                                                             shootingCount(0)
{
    pixmapItem->setPos(-50, -100);
    set_damage(6);
}

void Bow::mountToParent()
{
    Weapon::mountToParent();
    setTransform(QTransform().scale(1,1));
    setPos(-75,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -100);
    }
    setZValue(1);
    qDebug() << pos().x() << "" << pos().y() << pixmapItem->pos().x() << "" << pixmapItem->pos().y();
}

void Bow::unmount()
{
    Weapon::unmount();
    if (pixmapItem != nullptr)
    {

    }
}

void Bow::equippedToParent()
{
    Weapon::equippedToParent();
    mountToParent();
}

void Bow::unequippedFromParent()
{
    Weapon::unequippedFromParent();
    setTransform(QTransform().scale(-1,1));
    setPos(25,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -100);
    }
    setZValue(-2);
}
