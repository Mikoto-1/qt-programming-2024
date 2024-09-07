//
// Created by hp on 24-8-30.
//

#include "WoodPlatform.h"

#include "../Materials/WoodMaterial.h"

WoodPlatform::WoodPlatform(QGraphicsItem* parent): Platform(parent, ":/Items/Maps/Platforms/WoodPlatform.png")
{
    material = new WoodMaterial;
}
