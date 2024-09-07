//
// Created by hp on 24-8-31.
//

#include "LargeSword.h"

#include "../Effects/FireEffect.h"
#include "../Effects/LightningEffect.h"

LargeSword::LargeSword(QGraphicsItem* parent, const QString& pixmapPath) : MeleeWeapon(parent, pixmapPath)
{
    pixmapItem->setPos(-50, -85);
    attackingCountdown = 120;
    attackingSpeed = 6;
    set_damage(8);
}

void LargeSword::mountToParent()
{
    MeleeWeapon::mountToParent();
    setTransform(QTransform().scale(-1,1));
    setPos(-75,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -85);
    }
    setZValue(1);
    qDebug() << pos().x() << "" << pos().y() << pixmapItem->pos().x() << "" << pixmapItem->pos().y();
}

void LargeSword::unmount()
{
    MeleeWeapon::unmount();
    if (pixmapItem != nullptr)
    {
        //pixmapItem->setPos(0, 0);
    }
}

void LargeSword::equippedToParent()
{
    MeleeWeapon::equippedToParent();
    mountToParent();
}

void LargeSword::unequippedFromParent()
{
    MeleeWeapon::unequippedFromParent();
    setTransform(QTransform().scale(1,1));
    setPos(40,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -85);
    }
    setZValue(-1);
}
