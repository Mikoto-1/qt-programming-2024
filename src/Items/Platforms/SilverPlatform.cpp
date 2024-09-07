//
// Created by hp on 24-8-30.
//

#include "SilverPlatform.h"

#include "../Materials/MetalMaterial.h"

SilverPlatform::SilverPlatform(QGraphicsItem* parent):Platform(parent, ":/Items/Maps/Platforms/SilverPlatform.png")
{
    material = new MetalMaterial;
}
