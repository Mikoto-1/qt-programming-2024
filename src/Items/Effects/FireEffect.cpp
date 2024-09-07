//
// Created by hp on 24-9-5.
//

#include "FireEffect.h"

FireEffect::FireEffect(QGraphicsItem* parent) : Effect(parent, ":/Items/Effects/FireEffect")
{
    setScale(0.16);
    setZValue(2);
    initialCountdown = countdown = 270;
    spreadCountdown = 90;
    damagePerFrame = 0.02;
    type = "Fire";
}
