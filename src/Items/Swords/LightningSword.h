//
// Created by hp on 24-8-31.
//

#ifndef LIGHTNINGSWORD_H
#define LIGHTNINGSWORD_H
#include "Sword.h"
#include "../../DamageType/LightningDamage.h"


class LightningSword : public Sword
{
public:
    explicit LightningSword(QGraphicsItem* parent = nullptr);
};



#endif //LIGHTNINGSWORD_H
