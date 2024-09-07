//
// Created by hp on 24-9-4.
//

#ifndef DAMAGETYPE_H
#define DAMAGETYPE_H
#include <QString>


class DamageType {
public:
    virtual ~DamageType() = default;
    virtual QString getDamageType();
};



#endif //DAMAGETYPE_H
