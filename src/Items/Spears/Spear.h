//
// Created by hp on 24-8-31.
//

#ifndef SPEAR_H
#define SPEAR_H
#include "../MeleeWeapon.h"


class Spear : public MeleeWeapon
{
public:
    explicit Spear(QGraphicsItem* parent, const QString& pixmapPath);

    void mountToParent() override;

    void unmount() override;

    void equippedToParent() override;

    void unequippedFromParent() override;
};


#endif //SPEAR_H
