//
// Created by hp on 24-9-4.
//

#ifndef FIREDAMAGE_H
#define FIREDAMAGE_H
#include "DamageType.h"


class FireDamage : public DamageType
{
public:
    QString getDamageType() override;
};



#endif //FIREDAMAGE_H
