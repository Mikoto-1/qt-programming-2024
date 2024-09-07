//
// Created by hp on 24-8-30.
//

#include "BronzePlatform.h"

#include "../Materials/MetalMaterial.h"

BronzePlatform::BronzePlatform(QGraphicsItem* parent):Platform(parent, ":/Items/Maps/Platforms/BronzePlatform.png")
{
    material = new MetalMaterial;
}
