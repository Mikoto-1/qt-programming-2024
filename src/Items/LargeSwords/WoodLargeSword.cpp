//
// Created by hp on 24-8-31.
//

#include "WoodLargeSword.h"

#include "../Materials/MetalMaterial.h"
#include "../Materials/WoodMaterial.h"

WoodLargeSword::WoodLargeSword(QGraphicsItem* parent): LargeSword(parent, ":/Items/LargeSwords/WoodLargeSword.png")
{
    damageType1 = new OrdinaryDamage;
    material = new WoodMaterial;
}
