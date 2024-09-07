//
// Created by hp on 24-8-31.
//

#include "WoodSpear.h"

#include "../Materials/WoodMaterial.h"

WoodSpear::WoodSpear(QGraphicsItem* parent) : Spear(parent,":/Items/Spears/WoodSpear.png")
{
    damageType1 = new OrdinaryDamage;
    material = new WoodMaterial;
}
