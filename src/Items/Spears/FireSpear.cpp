//
// Created by hp on 24-9-1.
//

#include "FireSpear.h"

#include "../Materials/MetalMaterial.h"

FireSpear::FireSpear(QGraphicsItem* parent) : Spear(parent,":/Items/Spears/FireSpear.png")
{
    damageType = "Fire";
    damageType1 = new FireDamage;
    material = new MetalMaterial;
}
