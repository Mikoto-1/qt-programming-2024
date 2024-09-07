//
// Created by hp on 24-8-31.
//

#include "Spear.h"

#include "../Effects/FireEffect.h"
#include "../Effects/LightningEffect.h"

Spear::Spear(QGraphicsItem* parent, const QString& pixmapPath) : MeleeWeapon(parent, pixmapPath)
{
    pixmapItem->setPos(-50, -90);
    attackingCountdown = 60;
    attackingSpeed = 5;
    set_damage(5);
}

void Spear::mountToParent()
{
    MeleeWeapon::mountToParent();
    setTransform(QTransform().scale(-1,1));
    setPos(-80,-90);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -90);
    }
    setZValue(1);
    qDebug() << pos().x() << "" << pos().y() << pixmapItem->pos().x() << "" << pixmapItem->pos().y();
}

void Spear::unmount()
{
    MeleeWeapon::unmount();
    if (pixmapItem != nullptr)
    {
        //pixmapItem->setPos(0, 0);
    }
}

void Spear::equippedToParent()
{
    MeleeWeapon::equippedToParent();
    mountToParent();
}

void Spear::unequippedFromParent()
{
    MeleeWeapon::unequippedFromParent();
    setTransform(QTransform().scale(1,1));
    setPos(40,-90);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -90);
    }
    setZValue(-1);
}
