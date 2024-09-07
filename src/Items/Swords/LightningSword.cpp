//
// Created by hp on 24-8-31.
//

#include "LightningSword.h"

#include "../Materials/MetalMaterial.h"

LightningSword::LightningSword(QGraphicsItem* parent) : Sword(parent,":/Items/Swords/LightningSword.png")
{
    damageType = "Lightning";
    damageType1 = new LightningDamage;
    material = new MetalMaterial;
}
