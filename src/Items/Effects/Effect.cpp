//
// Created by hp on 24-9-5.
//

#include "Effect.h"

Effect::Effect(QGraphicsItem* parent, const QString& pixmapPath) : Item(parent, pixmapPath), countdown(0),
                                                                   initialCountdown(0)
{
}
