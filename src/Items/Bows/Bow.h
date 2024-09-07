//
// Created by hp on 24-8-31.
//

#ifndef BOW_H
#define BOW_H
#include "../Weapon.h"


class Bow : public Weapon
{
public:
    explicit Bow(QGraphicsItem* parent, const QString& pixmapPath);

    void mountToParent() override;

    void unmount() override;

    void equippedToParent() override;

    void unequippedFromParent() override;

    qreal initialVelocity{};

    int shootingCount{};
};


#endif //BOW_H
