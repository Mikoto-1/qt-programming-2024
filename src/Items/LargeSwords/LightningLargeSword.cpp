//
// Created by hp on 24-8-31.
//

#include "LightningLargeSword.h"

#include "../Materials/MetalMaterial.h"

LightningLargeSword::LightningLargeSword(QGraphicsItem* parent): LargeSword(parent, ":/Items/LargeSwords/LightningLargeSword.png")
{
    damageType = "Lightning";
    damageType1 = new LightningDamage;
    material = new MetalMaterial;
}
