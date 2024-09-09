//
// Created by hp on 24-9-1.
//

#include "MetalSpear.h"

#include "../Materials/MetalMaterial.h"

MetalSpear::MetalSpear(QGraphicsItem* parent) : Spear(parent,":/Items/Spears/MetalSpear.png")
{
    damageType1 = new OrdinaryDamage;
    material = new MetalMaterial;
}
