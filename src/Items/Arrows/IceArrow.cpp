//
// Created by hp on 24-9-2.
//

#include "IceArrow.h"

IceArrow::IceArrow(QGraphicsItem* parent) : Arrow(parent, ":/Items/Arrows/IceArrow.png")
{
    damageType = "Ice";
    damageType1 = new IceDamage;
}

QString IceArrow::getType()
{
    return "Ice";
}
