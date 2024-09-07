//
// Created by hp on 24-9-5.
//

#include "LightningEffect.h"

LightningEffect::LightningEffect(QGraphicsItem* parent) : Effect(parent, ":/Items/Effects/LightningEffect")
{
    setScale(1);
    setZValue(2);
    initialCountdown = countdown = 90;
    damagePerFrame = 0.08;
    type = "Lightning";
}
