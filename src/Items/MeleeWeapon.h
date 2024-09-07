//
// Created by hp on 24-8-31.
//

#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "Weapon.h"


class MeleeWeapon : public Weapon
{
public:
    explicit MeleeWeapon(QGraphicsItem* parent, const QString& pixmapPath);

    int attackingCountdown = 0;

    int attackingSpeed = 0;
};


#endif //MELEEWEAPON_H
