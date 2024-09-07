//
// Created by hp on 24-9-4.
//

#ifndef ICEDAMAGE_H
#define ICEDAMAGE_H
#include "DamageType.h"


class IceDamage : public DamageType
{
public:
    QString getDamageType() override;
};



#endif //ICEDAMAGE_H
