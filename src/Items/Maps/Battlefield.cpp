//
// Created by gerw on 8/21/24.
//

#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem* parent) : Map(parent, ":/Items/Maps/Battlefield/country-platform.png")
{
}

qreal Battlefield::getFloorHeight()
{
    auto sceneRect = sceneBoundingRect();
    return (sceneRect.top() + sceneRect.bottom()) * 0.87;
}
