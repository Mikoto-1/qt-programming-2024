//
// Created by hp on 24-9-1.
//

#include "OrdinaryWoodBow.h"

#include "../Materials/WoodMaterial.h"

OrdinaryWoodBow::OrdinaryWoodBow(QGraphicsItem* parent): Bow(parent, ":/Items/Bows/OrdinaryWoodBow.png")
{
    initialVelocity = 0.8;
    shootingCount = 1;
    damageType1 = new OrdinaryDamage;
    material = new WoodMaterial;
}
