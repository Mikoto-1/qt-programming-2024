//
// Created by hp on 24-8-31.
//

#include "Weapon.h"

#include "../DamageType/OrdinaryDamage.h"

Weapon::Weapon(QGraphicsItem* parent, const QString& pixmapPath): Item(parent, pixmapPath)
{
    // pixmapItem->setPos(-50, -80);
    bottomEllipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    // Optionally, set some properties of the ellipse
    bottomEllipseItem->setBrush(Qt::blue); // Fill color
    bottomEllipseItem->setZValue(1);
    topEllipseItem = new QGraphicsEllipseItem(-5, -105, 10, 10, this);
    topEllipseItem->setBrush(Qt::blue);
    topEllipseItem->setZValue(1);

    damageType1 = new OrdinaryDamage;
}

QPointF Weapon::getVelocity() const
{
    return velocity;
}

void Weapon::setVelocity(const QPointF& velocity)
{
    this->velocity = velocity;
}

bool Weapon::isInAir() const
{
    return inAir;
}

void Weapon::setInAir(const bool inAir)
{
    this->inAir = inAir;
}

bool Weapon::isEquipped() const
{
    return equipped;
}

void Weapon::setEquipped(const bool equipped)
{
    this->equipped = equipped;
}

void Weapon::equippedToParent()
{
    setEquipped(true);
}

void Weapon::unequippedFromParent()
{
    setEquipped(false);
}

bool Weapon::isOnAttack() const
{
    return onAttack;
}

void Weapon::setOnAttack(bool onAttack)
{
    this->onAttack = onAttack;
}

Character* Weapon::getHolder() const
{
    return holder;
}

void Weapon::setHolder(Character* holder)
{
    this->holder = holder;
}

int Weapon::get_damage() const
{
    return damage;
}

void Weapon::set_damage(const int damage)
{
    this->damage = damage;
}
