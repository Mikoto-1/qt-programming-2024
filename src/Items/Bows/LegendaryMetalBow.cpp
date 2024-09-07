//
// Created by hp on 24-9-1.
//

#include "LegendaryMetalBow.h"

#include "../Materials/MetalMaterial.h"

LegendaryMetalBow::LegendaryMetalBow(QGraphicsItem* parent): Bow(parent, ":/Items/Bows/LegendaryMetalBow.png")
{
    initialVelocity = 1;
    shootingCount = 2;
    damageType1 = new OrdinaryDamage;
    material = new MetalMaterial;
}
