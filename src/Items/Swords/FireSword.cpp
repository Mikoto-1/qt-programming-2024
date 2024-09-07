//
// Created by hp on 24-8-31.
//

#include "FireSword.h"

#include "../Materials/MetalMaterial.h"

FireSword::FireSword(QGraphicsItem* parent) : Sword(parent, ":/Items/Swords/FireSword.png")
{
    damageType = "Fire";
    damageType1 = new FireDamage;
    material = new MetalMaterial;
}
