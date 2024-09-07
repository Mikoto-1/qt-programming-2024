//
// Created by hp on 24-8-31.
//

#ifndef SWORD_H
#define SWORD_H
#include "../MeleeWeapon.h"


class Sword : public MeleeWeapon
{
public:
    explicit Sword(QGraphicsItem* parent, const QString& pixmapPath);

    void mountToParent() override;

    void unmount() override;

    void equippedToParent() override;

    void unequippedFromParent() override;
};


#endif //SWORD_H
