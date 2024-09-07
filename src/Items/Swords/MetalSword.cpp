//
// Created by hp on 24-8-31.
//

#include "MetalSword.h"

#include "../Materials/MetalMaterial.h"

MetalSword::MetalSword(QGraphicsItem* parent) : Sword(parent, ":/Items/Swords/MetalSword.png")
{
    damageType1 = new OrdinaryDamage;
    material = new MetalMaterial;
}
