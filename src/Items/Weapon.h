//
// Created by hp on 24-8-31.
//

#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Mountable.h"
#include "../DamageType/DamageType.h"
// #include "Characters/Character.h"
class Character;

class Weapon : public Item, public Mountable
{
public:
    explicit Weapon(QGraphicsItem* parent, const QString& pixmapPath);

    [[nodiscard]] QPointF getVelocity() const;

    void setVelocity(const QPointF& velocity);

    [[nodiscard]] bool isInAir() const;

    void setInAir(bool inAir);

    [[nodiscard]] bool isEquipped() const;

    void setEquipped(bool equipped);

    virtual void equippedToParent();

    virtual void unequippedFromParent();

    [[nodiscard]] bool isOnAttack() const;

    void setOnAttack(bool onAttack);

    [[nodiscard]] Character* getHolder() const;

    void setHolder(Character* holder);

    QString damageType = "";

    DamageType* damageType1 = nullptr;

private:
    QPointF velocity{};

    bool inAir = true;

    bool equipped = false;

    bool onAttack = false;

    int damage = 0;

public:
    [[nodiscard]] int get_damage() const;

    void set_damage(int damage);

private:
    Character* holder = nullptr;

    QGraphicsEllipseItem* bottomEllipseItem; // For debugging.

    QGraphicsEllipseItem* topEllipseItem; // For debugging.
};


#endif //WEAPON_H
