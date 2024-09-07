//
// Created by hp on 24-9-2.
//

#include "LightningArrow.h"

LightningArrow::LightningArrow(QGraphicsItem* parent) : Arrow(parent,":/Items/Arrows/LightningArrow.png")
{
    damageType = "Lightning";
    damageType1 = new LightningDamage;
}

QString LightningArrow::getType()
{
    return "Lightning";
}
