//
// Created by hp on 24-9-5.
//

#include "IceEffect.h"

IceEffect::IceEffect(QGraphicsItem* parent) : Effect(parent, ":/Items/Effects/IceEffect")
{
    setScale(0.5);
    setZValue(2);
    initialCountdown = countdown = 270;
    type = "Ice";
}
