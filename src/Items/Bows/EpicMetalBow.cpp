//
// Created by hp on 24-9-1.
//

#include "EpicMetalBow.h"

#include "../Materials/MetalMaterial.h"

EpicMetalBow::EpicMetalBow(QGraphicsItem* parent): Bow(parent, ":/Items/Bows/EpicMetalBow.png")
{
    initialVelocity = 1.2;
    shootingCount = 3;
    damageType1 = new OrdinaryDamage;
    material = new MetalMaterial;
}
