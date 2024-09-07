//
// Created by hp on 24-8-31.
//

#ifndef LARGESWORD_H
#define LARGESWORD_H
#include "../MeleeWeapon.h"


class LargeSword : public MeleeWeapon
{
public:
    explicit LargeSword(QGraphicsItem* parent, const QString& pixmapPath);

    void mountToParent() override;

    void unmount() override;

    void equippedToParent() override;

    void unequippedFromParent() override;
};


#endif //LARGESWORD_H
