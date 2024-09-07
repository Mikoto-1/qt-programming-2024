//
// Created by hp on 24-9-1.
//

#include "LightningSpear.h"

#include "../Materials/MetalMaterial.h"

LightningSpear::LightningSpear(QGraphicsItem* parent) : Spear(parent,":/Items/Spears/LightningSpear.png")
{
    damageType = "Lightning";
    damageType1 = new LightningDamage;
    material = new MetalMaterial;
}
