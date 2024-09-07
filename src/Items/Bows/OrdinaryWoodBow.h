//
// Created by hp on 24-9-1.
//

#ifndef ORDINARYWOODBOW_H
#define ORDINARYWOODBOW_H
#include "Bow.h"
#include "../../DamageType/OrdinaryDamage.h"


class OrdinaryWoodBow : public Bow
{
public:
    explicit OrdinaryWoodBow(QGraphicsItem* parent = nullptr);
};



#endif //ORDINARYWOODBOW_H
