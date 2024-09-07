//
// Created by gerw on 8/20/24.
//

#include "Item.h"

#include "Effects/Effect.h"

Item::Item(QGraphicsItem* parent, const QString& pixmapPath) : QGraphicsItem(parent)
{
    if (pixmapPath != "")
    {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(pixmapPath), this);
    }
    material = new Material;
}

void Item::removeEffect()
{
    for (auto & effect : effects)
    {
        delete effect;
        effect = nullptr;
    }
    effects.clear();
    currentEffect = nullptr;
}
