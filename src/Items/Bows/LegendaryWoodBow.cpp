//
// Created by hp on 24-9-1.
//

#include "LegendaryWoodBow.h"

#include "../Materials/WoodMaterial.h"

LegendaryWoodBow::LegendaryWoodBow(QGraphicsItem* parent): Bow(parent, ":/Items/Bows/LegendaryWoodBow.png")
{
    initialVelocity = 1;
    shootingCount = 2;
    damageType1 = new OrdinaryDamage;
    material = new WoodMaterial;
}
