//
// Created by hp on 24-9-1.
//

#include "OrdinaryMetalBow.h"

#include "../Materials/MetalMaterial.h"

OrdinaryMetalBow::OrdinaryMetalBow(QGraphicsItem* parent): Bow(parent, ":/Items/Bows/OrdinaryMetalBow.png")
{
    initialVelocity = 0.8;
    shootingCount = 1;
    damageType1 = new OrdinaryDamage;
    material = new MetalMaterial;
}
