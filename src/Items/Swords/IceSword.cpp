//
// Created by hp on 24-8-31.
//

#include "IceSword.h"

#include "../Materials/MetalMaterial.h"

IceSword::IceSword(QGraphicsItem* parent):Sword(parent,":/Items/Swords/IceSword.png")
{
    damageType = "Ice";
    damageType1 = new IceDamage;
    material = new MetalMaterial;
}
