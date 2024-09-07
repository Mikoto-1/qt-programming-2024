//
// Created by hp on 24-9-1.
//

#include "IceSpear.h"

#include "../Materials/MetalMaterial.h"

IceSpear::IceSpear(QGraphicsItem* parent) : Spear(parent,":/Items/Spears/IceSpear.png")
{
    damageType = "Ice";
    damageType1 = new IceDamage;
    material = new MetalMaterial;
}
