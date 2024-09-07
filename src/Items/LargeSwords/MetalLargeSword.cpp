//
// Created by hp on 24-8-31.
//

#include "MetalLargeSword.h"

#include "../Materials/MetalMaterial.h"

MetalLargeSword::MetalLargeSword(QGraphicsItem* parent): LargeSword(parent, ":/Items/LargeSwords/MetalLargeSword.png")
{
    damageType1 = new OrdinaryDamage;
    material = new MetalMaterial;
}
