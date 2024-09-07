//
// Created by hp on 24-8-31.
//

#include "WoodSword.h"

#include "../Materials/WoodMaterial.h"

WoodSword::WoodSword(QGraphicsItem* parent) : Sword(parent,":/Items/Swords/WoodSword.png")
{
    damageType1 = new OrdinaryDamage;
    material = new WoodMaterial;
}
