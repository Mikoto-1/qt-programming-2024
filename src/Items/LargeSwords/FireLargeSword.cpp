//
// Created by hp on 24-8-31.
//

#include "FireLargeSword.h"

#include "../Materials/MetalMaterial.h"

FireLargeSword::FireLargeSword(QGraphicsItem* parent): LargeSword(parent, ":/Items/LargeSwords/FireLargeSword.png")
{
    damageType = "Fire";
    damageType1 = new FireDamage;
    material = new MetalMaterial;
}
