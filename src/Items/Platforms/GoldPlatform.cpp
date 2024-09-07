//
// Created by hp on 24-8-30.
//

#include "GoldPlatform.h"

#include "../Materials/MetalMaterial.h"

GoldPlatform::GoldPlatform(QGraphicsItem* parent):Platform(parent, ":/Items/Maps/Platforms/GoldPlatform.png")
{
    material = new MetalMaterial;
}
