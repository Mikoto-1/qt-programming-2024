//
// Created by hp on 24-8-31.
//

#ifndef WOODSWORD_H
#define WOODSWORD_H
#include "Sword.h"
#include "../../DamageType/OrdinaryDamage.h"


class WoodSword : public Sword
{
public:
    explicit WoodSword(QGraphicsItem* parent = nullptr);
};


#endif //WOODSWORD_H
