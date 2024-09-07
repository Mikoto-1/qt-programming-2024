//
// Created by hp on 24-9-4.
//

#ifndef LIGHTNINGDAMAGE_H
#define LIGHTNINGDAMAGE_H
#include "DamageType.h"


class LightningDamage : public DamageType
{
public:
    QString getDamageType() override;
};



#endif //LIGHTNINGDAMAGE_H
