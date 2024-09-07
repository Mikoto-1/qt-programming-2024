//
// Created by gerw on 8/20/24.
//

#include <QTransform>
#include "Character.h"

#include <bits/fs_fwd.h>

#include "../Arrows/Arrow.h"
#include "../Arrows/OrdinaryArrow.h"
#include "../Effects/IceEffect.h"
#include "../LargeSwords/FireLargeSword.h"
#include "../LargeSwords/IceLargeSword.h"
#include "../LargeSwords/LargeSword.h"
#include "../LargeSwords/LightningLargeSword.h"
#include "../LargeSwords/MetalLargeSword.h"
#include "../LargeSwords/WoodLargeSword.h"
#include "../Spears/Spear.h"
#include "../Swords/Sword.h"

Character::Character(QGraphicsItem* parent) : Item(parent, "")
{
    bottomEllipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    // Optionally, set some properties of the ellipse
    bottomEllipseItem->setBrush(Qt::green); // Fill color
    bottomEllipseItem->setZValue(1);
    topEllipseItem = new QGraphicsEllipseItem(-5, -205, 10, 10, this);
    topEllipseItem->setBrush(Qt::green);
    topEllipseItem->setZValue(1);
    setInAir(false);
    hitPoints = maxHitPoints;

    for (auto arrow : arrows_)
    {
        arrow->unequippedFromParent();
        arrow->setVisible(false);
        arrow->setMountable(false);
    }
    for (const auto& key : arrowNumbers.keys())
    {
        qDebug() << "type: " << key;
    }
}

bool Character::isLeftDown() const
{
    return leftDown;
}

void Character::setLeftDown(bool leftDown)
{
    Character::leftDown = leftDown;
}

bool Character::isRightDown() const
{
    return rightDown;
}

void Character::setRightDown(bool rightDown)
{
    Character::rightDown = rightDown;
}

bool Character::isToLeft() const
{
    return toLeft;
}

void Character::setToLeft(bool toLeft)
{
    Character::toLeft = toLeft;
    toRight = !toLeft;
}

bool Character::isToRight() const
{
    return toRight;
}

void Character::setToRight(bool toRight)
{
    Character::toRight = toRight;
    toLeft = !toRight;
}

bool Character::isPickDown() const
{
    return pickDown;
}

void Character::setPickDown(bool pickDown)
{
    Character::pickDown = pickDown;
}

bool Character::isInAir() const
{
    return inAir;
}

void Character::setInAir(bool inAir)
{
    Character::inAir = inAir;
}

const QPointF& Character::getVelocity() const
{
    return velocity;
}

void Character::setVelocity(const QPointF& velocity)
{
    Character::velocity = velocity;
}

void Character::startJumping()
{
    constexpr auto initialVerticalVelocity = -1.2;
    velocity.setY(initialVerticalVelocity);
    setInAir(true);
}

qreal Character::getTopHeight() const
{
    return pos().y() - 200;
}

qreal Character::getBottomHeight() const
{
    return pos().y();
}

void Character::processInput()
{
    auto velocity = QPointF(0, 0);
    constexpr auto moveSpeed = 0.3;
    if (isLeftDown())
    {
        velocity.setX(velocity.x() - moveSpeed);
        setTransform(QTransform().scale(1, 1));
    }
    if (isRightDown())
    {
        velocity.setX(velocity.x() + moveSpeed);
        setTransform(QTransform().scale(-1, 1));
    }
    velocity.setY(getVelocity().y());
    setVelocity(velocity);

    if (!lastPickDown && pickDown)
    {
        // first time pickDown
        picking = true;
    }
    else
    {
        picking = false;
    }
    lastPickDown = pickDown;
}

void Character::processAttacking()
{
    if (currentWeapon != nullptr && currentWeapon == meleeWeapon)
    {
        if (!attacking)
        {
            return;
        }
        auto melee = dynamic_cast<MeleeWeapon*>(currentWeapon);
        auto countdown = melee->attackingCountdown;
        if (attackingCountdown <= 0)
        {
            attackingCountdown = countdown;
        }
        if (dynamic_cast<Sword*>(melee) || dynamic_cast<Spear*>(melee))
        {
            if (attackingCountdown > countdown / 2)
            {
                currentWeapon->setPos(currentWeapon->pos() - QPointF(melee->attackingSpeed, 0));
            }
            else if (attackingCountdown > 0)
            {
                currentWeapon->setPos(currentWeapon->pos() + QPointF(melee->attackingSpeed, 0));
            }
        }
        if (auto largeSword = dynamic_cast<LargeSword*>(melee))
        {
            if (backwardWeapon == nullptr)
            {
                LargeSword* newLargeSword = nullptr;
                if (dynamic_cast<FireLargeSword*>(largeSword))
                {
                    newLargeSword = new FireLargeSword(this);
                }
                else if (dynamic_cast<IceLargeSword*>(largeSword))
                {
                    newLargeSword = new IceLargeSword(this);
                }
                else if (dynamic_cast<LightningLargeSword*>(largeSword))
                {
                    newLargeSword = new LightningLargeSword(this);
                }
                else if (dynamic_cast<WoodLargeSword*>(largeSword))
                {
                    newLargeSword = new WoodLargeSword(this);
                }
                else if (dynamic_cast<MetalLargeSword*>(largeSword))
                {
                    newLargeSword = new MetalLargeSword(this);
                }
                backwardWeapon = newLargeSword;
                if (backwardWeapon != nullptr)
                {
                    backwardWeapon->mountToParent();
                    backwardWeapon->setTransform(QTransform().scale(1, 1));
                    backwardWeapon->setPos(-currentWeapon->pos().x(),currentWeapon->pos().y());
                }
            }
            if (attackingCountdown > countdown / 2)
            {

            }
            else if (attackingCountdown > countdown / 4)
            {
                currentWeapon->setPos(currentWeapon->pos() - QPointF(melee->attackingSpeed, 0));
                if (backwardWeapon != nullptr)
                {
                    backwardWeapon->setPos(backwardWeapon->pos() + QPointF(melee->attackingSpeed, 0));
                }
            }
            else if (attackingCountdown > 0)
            {
                currentWeapon->setPos(currentWeapon->pos() + QPointF(melee->attackingSpeed, 0));
                if (backwardWeapon != nullptr)
                {
                    backwardWeapon->setPos(backwardWeapon->pos() - QPointF(melee->attackingSpeed, 0));
                }
            }
        }
        // qDebug() << "current weapon position:" << currentWeapon->pos();
        // qDebug() << "backward weapon position:" << backwardWeapon->pos();
        attackingCountdown -= 1;
        if (attackingCountdown <= 0)
        {
            attacking = false;
            if (backwardWeapon != nullptr)
            {
                delete backwardWeapon;
                backwardWeapon = nullptr;
            }
        }
    }
}

void Character::processDamage(qreal damage)
{
    if (currentEffect != nullptr && dynamic_cast<IceEffect*>(currentEffect) != nullptr)
    {
        setHitPoints(hitPoints - 2 * damage);
        removeEffect();
        currentEffect = nullptr;
    }
    else
    {
        setHitPoints(hitPoints - damage);
    }
}

bool Character::isPicking() const
{
    return picking;
}

Armor* Character::pickupArmor(Armor* newArmor)
{
    auto oldArmor = armor;
    if (oldArmor != nullptr)
    {
        oldArmor->unmount();
        oldArmor->setPos(newArmor->pos());
        oldArmor->setParentItem(parentItem());
    }
    newArmor->setParentItem(this);
    newArmor->mountToParent();
    armor = newArmor;
    return oldArmor;
}

void Character::pickupArmorSuit(ArmorSuit* newArmSuit)
{
    auto oldArmorSuit = armorSuit;
    if (oldArmorSuit != nullptr)
    {
        oldArmorSuit->unmount();
        oldArmorSuit->setPos(newArmSuit->pos());
        oldArmorSuit->setParentItem(parentItem());
    }
    newArmSuit->setParentItem(this);
    newArmSuit->mountToParent();
    armorSuit = newArmSuit;
    armor = armorSuit->armor;
    legEquipment = armorSuit->legEquipment;
    headEquipment = armorSuit->headEquipment;
}

void Character::pickupWeapon(Weapon* newWeapon)
{
    if (const auto newMeleeWeapon = dynamic_cast<MeleeWeapon*>(newWeapon))
    {
        if (meleeWeapon != nullptr)
        {
            return;
        }
        newWeapon->setParentItem(this);
        newWeapon->mountToParent();
        meleeWeapon = newMeleeWeapon;
        if (currentWeapon == nullptr)
        {
            currentWeapon = meleeWeapon;
            currentWeapon->equippedToParent();
        }
        else
        {
            unusedWeapon = meleeWeapon;
            unusedWeapon->unequippedFromParent();
        }
        return;
    }
    if (const auto newBow = dynamic_cast<Bow*>(newWeapon))
    {
        if (bow != nullptr)
        {
            return;
        }
        newBow->setParentItem(this);
        newBow->mountToParent();
        bow = newBow;
        if (currentWeapon == nullptr)
        {
            currentWeapon = bow;
            currentWeapon->equippedToParent();
            // currentArrow->equippedToParent();
            for (auto arrow : arrows_)
            {
                arrow->equippedToParent();
            }
        }
        else
        {
            unusedWeapon = bow;
            unusedWeapon->unequippedFromParent();
            // currentArrow->unequippedFromParent();
            for (auto arrow : arrows_)
            {
                arrow->unequippedFromParent();
            }
        }
    }
    if (const auto newArrow = dynamic_cast<Arrow*>(newWeapon))
    {
        newArrow->setParentItem(this);
        newArrow->mountToParent();
        arrowNumbers[newArrow->getType()] += 5;
        if (currentArrow == nullptr)
        {
            currentArrow = newArrow;
            currentArrow->setVisible(true);
        }
        else
        {
            newArrow->setVisible(false);
        }
        if (currentWeapon != nullptr && currentWeapon == meleeWeapon)
        {
            // currentArrow->unequippedFromParent();
            for (auto arrow : arrows_)
            {
                arrow->unequippedFromParent();
            }
        }
    }
}

void Character::pickupArrow(Arrow* newArrow)
{
    if (newArrow == nullptr)
    {
        return;
    }
    if (currentArrow == nullptr)
    {
        currentArrow = arrows_[newArrow->getType()];
        if (currentArrow != nullptr)
        {
            currentArrow->setVisible(true);
        }
    }
    arrowNumbers[newArrow->getType()] += 5;
}

Weapon* Character::discardWeapon()
{
    if (currentWeapon != nullptr)
    {
        if (currentWeapon == meleeWeapon)
        {
            const auto onAttackMeleeWeapon = currentWeapon;
            currentWeapon = meleeWeapon = nullptr;
            onAttackMeleeWeapon->unmount();
            onAttackMeleeWeapon->setInAir(true);
            onAttackMeleeWeapon->setEquipped(false);
            auto relativePosition = onAttackMeleeWeapon->pos();
            onAttackMeleeWeapon->setParentItem(parentItem());
            if (isToLeft())
            {
                // onAttackMeleeWeapon->setTransform(QTransform().scale(-1, 1));
                onAttackMeleeWeapon->setPos(this->pos() + relativePosition);
                onAttackMeleeWeapon->setVelocity(QPointF(-1, 0));
            }
            if (isToRight())
            {
                // onAttackMeleeWeapon->setTransform(QTransform().scale(-1, 1));
                onAttackMeleeWeapon->setTransform(QTransform().scale(1, 1));
                relativePosition.setX(-relativePosition.x());
                onAttackMeleeWeapon->setPos(this->pos() + relativePosition);
                onAttackMeleeWeapon->setVelocity(QPointF(1, 0));
            }
            return onAttackMeleeWeapon;
        }
        if (currentWeapon == bow)
        {
            const auto onAttackBow = currentWeapon;
            currentWeapon = bow = nullptr;
            onAttackBow->unmount();
            onAttackBow->setInAir(true);
            auto relativePosition = onAttackBow->pos();
            onAttackBow->setParentItem(parentItem());
            if (isToLeft())
            {
                onAttackBow->setTransform(QTransform().scale(1, 1));
                onAttackBow->setPos(this->pos() + relativePosition);
                onAttackBow->setVelocity(QPointF(-1, 0));
            }
            if (isToRight())
            {
                onAttackBow->setTransform(QTransform().scale(-1, 1));
                relativePosition.setX(-relativePosition.x());
                onAttackBow->setPos(this->pos() + relativePosition);
                onAttackBow->setVelocity(QPointF(1, 0));
            }

            // currentArrow->unequippedFromParent();
            for (auto arrow : arrows_)
            {
                arrow->unequippedFromParent();
            }
            return onAttackBow;
        }
        return nullptr;
    }
    return nullptr;
}

QList<Arrow*> Character::shootArrow()
{
    QList<Arrow*> arrows;
    if (currentWeapon == nullptr)
    {
        return arrows;
    }
    if (currentWeapon == meleeWeapon)
    {
        return arrows;
    }
    if (currentArrow != nullptr)
    {
        if (currentArrow->isVisible())
        {
            int arrow_number = std::min(dynamic_cast<Bow*>(currentWeapon)->shootingCount,arrowNumbers[currentArrow->getType()]);
            arrowNumbers[currentArrow->getType()] -= arrow_number;
            for (int i = 0; i < arrow_number; i++)
            {
                Arrow* arrow = nullptr;
                auto type = currentArrow->getType();
                if (type == "Ordinary")
                {
                    arrow = new OrdinaryArrow();
                }
                if (type == "Fire")
                {
                    arrow = new FireArrow();
                }
                if (type == "Ice")
                {
                    arrow = new IceArrow();
                }
                if (type == "Lightning")
                {
                    arrow = new LightningArrow();
                }
                if (arrow != nullptr)
                {
                    arrow->setVisible(true);
                    arrow->unmount();
                    arrow->setInAir(true);
                    auto relativePosition = currentArrow->pos();
                    if (isToLeft())
                    {
                        arrow->setPos(this->pos() + relativePosition + QPointF(0, -40*i));
                        arrow->setVelocity(QPointF(-dynamic_cast<Bow*>(currentWeapon)->initialVelocity, 0));
                    }
                    if (isToRight())
                    {
                        arrow->setTransform(QTransform().scale(-1, 1));
                        relativePosition.setX(-relativePosition.x());
                        arrow->setPos(this->pos() + relativePosition + QPointF(0, -40*i));
                        arrow->setVelocity(QPointF(dynamic_cast<Bow*>(currentWeapon)->initialVelocity, 0));
                    }
                    arrows.append(arrow);
                }
            }

            if (arrowNumbers[currentArrow->getType()] == 0)
            {

                switchArrow();
            }
        }
    }
    return arrows;
}

void Character::switchWeapon()
{
    if (meleeWeapon != nullptr && bow != nullptr)
    {
        if (currentWeapon == meleeWeapon)
        {
            meleeWeapon->unequippedFromParent();
            bow->equippedToParent();
            currentWeapon = bow;
            unusedWeapon = meleeWeapon;
            // currentArrow->equippedToParent();
            for(auto arrow : arrows_)
            {
                arrow->equippedToParent();
            }
            return;
        }
        if (currentWeapon == bow)
        {
            bow->unequippedFromParent();
            meleeWeapon->equippedToParent();
            currentWeapon = meleeWeapon;
            unusedWeapon = bow;
            // currentArrow->unequippedFromParent();
            for (auto arrow : arrows_)
            {
                arrow->unequippedFromParent();
            }
        }
        return;
    }
    if (currentWeapon == nullptr)
    {
        if (unusedWeapon == nullptr)
        {
            return;
        }
        if (unusedWeapon == meleeWeapon)
        {
        }
        currentWeapon = unusedWeapon;
        currentWeapon->equippedToParent();
        unusedWeapon = nullptr;
        if (currentWeapon == bow)
        {
            // currentArrow->equippedToParent();
            for (auto arrow : arrows_)
            {
                arrow->equippedToParent();
            }
        }
        else
        {
            // currentArrow->unequippedFromParent();
            for (auto arrow : arrows_)
            {
                arrow->unequippedFromParent();
            }
        }
        return;
    }
    if (unusedWeapon == nullptr)
    {
        unusedWeapon = currentWeapon;
        unusedWeapon->unequippedFromParent();
        currentWeapon = nullptr;
    }
    // currentArrow->unequippedFromParent();
    for (auto arrow : arrows_)
    {
        arrow->unequippedFromParent();
    }
}

void Character::switchArrow()
{
    if (currentArrow == nullptr)
    {
        return;
    }
    auto itr = arrowNumbers.begin();
    for (; itr != arrowNumbers.end(); ++itr)
    {
        if(itr.key() == currentArrow->getType())
        {
            break;
        }
    }
    auto currentItr = itr;
    ++itr;
    for (; itr != arrowNumbers.end(); ++itr)
    {
        if(itr.value() > 0)
        {
            currentArrow->setVisible(false);
            currentArrow = arrows_[itr.key()];
            currentArrow->setVisible(true);
            return;
        }
    }
    if (itr == arrowNumbers.end())
    {
        itr = arrowNumbers.begin();
        for (; itr != currentItr; ++itr)
        {
            if(itr.value() > 0)
            {
                currentArrow->setVisible(false);
                currentArrow = arrows_[itr.key()];
                currentArrow->setVisible(true);
                return;
            }
        }
    }
    if (itr == currentItr && itr.value() == 0)
    {
        currentArrow->setVisible(false);
        currentArrow = nullptr;
    }
}

bool Character::isOnAttack() const
{
    if (currentWeapon != nullptr)
    {
        return true;
    }
    return false;
}

bool Character::isUsingMelee() const
{
    if (currentWeapon != nullptr)
    {
        if (currentWeapon == meleeWeapon)
        {
            return true;
        }
    }
    return false;
}

bool Character::isUsingBow() const
{
    if (currentWeapon != nullptr)
    {
        if (currentWeapon == bow)
        {
            return true;
        }
    }
    return false;
}

bool Character::isAttacking() const
{
    return attacking;
}

void Character::setAttacking(const bool attacking)
{
    this->attacking = attacking;
}

Weapon* Character::getCurrentWeapon() const
{
    return currentWeapon;
}

void Character::setCurrentWeapon(Weapon* weapon)
{
    this->currentWeapon = weapon;
}

Weapon* Character::getUnusedWeapon() const
{
    return unusedWeapon;
}

void Character::setUnusedWeapon(Weapon* weapon)
{
    this->unusedWeapon = weapon;
}

Weapon* Character::getMeleeWeapon() const
{
    return meleeWeapon;
}

void Character::setMeleeWeapon(Weapon* weapon)
{
    meleeWeapon = dynamic_cast<MeleeWeapon*>(weapon);
}

Weapon* Character::getBow() const
{
    return bow;
}

void Character::setBow(Weapon* weapon)
{
    bow = dynamic_cast<Bow*>(weapon);
}

ArmorSuit* Character::getArmorSuit() const
{
    return armorSuit;
}

Arrow* Character::getCurrentArrow() const
{
    return currentArrow;
}

qreal Character::getHitPoints() const
{
    return hitPoints;
}

void Character::setHitPoints(const qreal hit_points)
{
    hitPoints = hit_points;
    if (hitPoints < 0)
    {
        hitPoints = 0;
    }
}
