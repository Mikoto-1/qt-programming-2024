//
// Created by hp on 24-8-31.
//

#ifndef METALSWORD_H
#define METALSWORD_H
#include "Sword.h"
#include "../../DamageType/OrdinaryDamage.h"


class MetalSword : public Sword
{
public:
    explicit MetalSword(QGraphicsItem* parent = nullptr);
};



#endif //METALSWORD_H
