//
// Created by hp on 24-9-1.
//

#include "EpicWoodBow.h"

#include "../Materials/WoodMaterial.h"

EpicWoodBow::EpicWoodBow(QGraphicsItem* parent): Bow(parent, ":/Items/Bows/EpicWoodBow.png")
{
    initialVelocity = 1.2;
    shootingCount = 3;
    damageType1 = new OrdinaryDamage;
    material = new WoodMaterial;
}
