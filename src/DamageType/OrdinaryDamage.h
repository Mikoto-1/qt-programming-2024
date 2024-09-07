//
// Created by hp on 24-9-4.
//

#ifndef ORDINARYDAMAGE_H
#define ORDINARYDAMAGE_H
#include "DamageType.h"


class OrdinaryDamage : public DamageType
{
public:
    QString getDamageType() override;
};



#endif //ORDINARYDAMAGE_H
