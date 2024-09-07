//
// Created by hp on 24-8-31.
//

#include "Sword.h"

#include "../Effects/FireEffect.h"
#include "../Effects/LightningEffect.h"

Sword::Sword(QGraphicsItem* parent, const QString& pixmapPath) : MeleeWeapon(parent, pixmapPath)
{
    pixmapItem->setPos(-50, -80);
    attackingCountdown = 60;
    attackingSpeed = 3;
    set_damage(6);
}

void Sword::mountToParent()
{
    MeleeWeapon::mountToParent();
    setTransform(QTransform().scale(-1,1));
    setPos(-70,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -80);
    }
    setZValue(1);
    qDebug() << pos().x() << "" << pos().y() << pixmapItem->pos().x() << "" << pixmapItem->pos().y();
}

void Sword::unmount()
{
    MeleeWeapon::unmount();
    if (pixmapItem != nullptr)
    {
        //pixmapItem->setPos(0, 0);
    }
}

void Sword::equippedToParent()
{
    MeleeWeapon::equippedToParent();
    mountToParent();
}

void Sword::unequippedFromParent()
{
    MeleeWeapon::unequippedFromParent();
    setTransform(QTransform().scale(1,1));
    setPos(40,-100);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(-50, -80);
    }
    setZValue(-1);
}
