//
// Created by hp on 24-9-2.
//

#include "OrdinaryArrow.h"

OrdinaryArrow::OrdinaryArrow(QGraphicsItem* parent) : Arrow(parent,":/Items/Arrows/Arrow.png")
{
    damageType1 = new OrdinaryDamage;
}

QString OrdinaryArrow::getType()
{
    return "Ordinary";
}
