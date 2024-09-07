//
// Created by hp on 24-8-31.
//

#include "IceLargeSword.h"

#include "../Materials/MetalMaterial.h"

IceLargeSword::IceLargeSword(QGraphicsItem* parent): LargeSword(parent, ":/Items/LargeSwords/IceLargeSword.png")
{
    damageType = "Ice";
    damageType1 = new IceDamage;
    material = new MetalMaterial;
}
