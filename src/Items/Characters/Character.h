//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_CHARACTER_H
#define QT_PROGRAMMING_2024_CHARACTER_H

#include <QGraphicsEllipseItem>

#include "../MeleeWeapon.h"
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../ArmorSuits/ArmorSuit.h"
#include "../Arrows/Arrow.h"
#include "../Arrows/FireArrow.h"
#include "../Arrows/IceArrow.h"
#include "../Arrows/LightningArrow.h"
#include "../Arrows/OrdinaryArrow.h"
#include "../Bows/Bow.h"
#include "../LegEquipments/LegEquipment.h"

class Character : public Item
{
public:
    explicit Character(QGraphicsItem* parent);

    [[nodiscard]] bool isLeftDown() const;

    void setLeftDown(bool leftDown);

    [[nodiscard]] bool isRightDown() const;

    void setRightDown(bool rightDown);

    [[nodiscard]] bool isToLeft() const;

    void setToLeft(bool toLeft);

    [[nodiscard]] bool isToRight() const;

    void setToRight(bool toRight);

    [[nodiscard]] bool isPickDown() const;

    void setPickDown(bool pickDown);

    [[nodiscard]] bool isInAir() const;

    void setInAir(bool inAir);

    [[nodiscard]] const QPointF& getVelocity() const;

    [[nodiscard]] bool isPicking() const;

    void setVelocity(const QPointF& velocity);

    void startJumping();

    [[nodiscard]] qreal getTopHeight() const;

    [[nodiscard]] qreal getBottomHeight() const;

    void processInput();

    void processAttacking();

    void processDamage(qreal damage);

    Armor* pickupArmor(Armor* newArmor);

    void pickupArmorSuit(ArmorSuit* newArmSuit);

    void pickupWeapon(Weapon* newWeapon);

    void pickupArrow(Arrow* newArrow);

    Weapon* discardWeapon();

    QList<Arrow*> shootArrow();

    void switchWeapon();

    void switchArrow();

    [[nodiscard]] bool isOnAttack() const;

    [[nodiscard]] bool isUsingMelee() const;

    [[nodiscard]] bool isUsingBow() const;

    [[nodiscard]] bool isAttacking() const;

    void setAttacking(bool attacking);

    [[nodiscard]] Weapon* getCurrentWeapon () const;

    void setCurrentWeapon(Weapon* weapon);

    [[nodiscard]] Weapon* getUnusedWeapon () const;

    void setUnusedWeapon(Weapon* weapon);

    [[nodiscard]] Weapon* getMeleeWeapon () const;

    void setMeleeWeapon(Weapon* weapon);

    [[nodiscard]] Weapon* getBow () const;

    void setBow(Weapon* weapon);

    [[nodiscard]] ArmorSuit* getArmorSuit() const;

    [[nodiscard]] Arrow* getCurrentArrow() const;

    const qreal maxHitPoints = 100;

    bool damageDone = false;

    QMap<QString, int> arrowNumbers = {{"Ordinary", 0}, {"Fire", 0}, {"Ice", 0}, {"Lightning", 0}};
    // QList<Arrow*> arrows = {new OrdinaryArrow(this), new FireArrow(this), new IceArrow(this), new LightningArrow(this)};
    QMap<QString, Arrow*> arrows_ = {
        {"Ordinary", new OrdinaryArrow(this)}, {"Fire", new FireArrow(this)}, {"Ice", new IceArrow(this)},
        {"Lightning", new LightningArrow(this)}
    };

protected:
    HeadEquipment* headEquipment{nullptr};
    LegEquipment* legEquipment{nullptr};
    Armor* armor{nullptr};
    ArmorSuit* armorSuit{nullptr};
    MeleeWeapon* meleeWeapon{nullptr};
    Bow* bow{nullptr};
    Weapon* currentWeapon{nullptr};
    Weapon* unusedWeapon{nullptr};
    Weapon* backwardWeapon{nullptr};
    Arrow* currentArrow{nullptr};
    QPointF velocity{};
    qreal hitPoints{0};

public:
    [[nodiscard]] qreal getHitPoints() const;

    void setHitPoints(qreal hit_points);

protected:
    QGraphicsEllipseItem* bottomEllipseItem; // for debugging
    QGraphicsEllipseItem* topEllipseItem;

private:
    bool leftDown{}, rightDown{}, pickDown{}, inAir{}, toLeft{}, toRight{};
    bool lastPickDown{};
    bool picking{}, attacking{};
    int attackingCountdown{};
};

#endif //QT_PROGRAMMING_2024_CHARACTER_H
