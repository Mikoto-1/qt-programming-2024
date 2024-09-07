//
// Created by hp on 24-9-2.
//

#include "FireArrow.h"

FireArrow::FireArrow(QGraphicsItem* parent) : Arrow(parent,":/Items/Arrows/FireArrow.png")
{
    damageType = "Fire";
    damageType1 = new FireDamage;
}

QString FireArrow::getType()
{
    return "Fire";
}
