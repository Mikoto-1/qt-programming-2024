//
// Created by gerw on 8/20/24.
//

#include "BattleScene.h"

#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QLineF>
#include <QMainWindow>
#include <QRandomGenerator>
#include <QString>

#include "../Items/Armors/FireProofArmor.h"
#include "../Items/ArmorSuits/ColdProofArmorSuit.h"
#include "../Items/ArmorSuits/FireProofArmorSuit.h"
#include "../Items/ArmorSuits/LightningProofArmorSuit.h"
#include "../Items/ArmorSuits/OrdinarySuit.h"
#include "../Items/Arrows/FireArrow.h"
#include "../Items/Arrows/IceArrow.h"
#include "../Items/Arrows/LightningArrow.h"
#include "../Items/Arrows/OrdinaryArrow.h"
#include "../Items/Bows/EpicMetalBow.h"
#include "../Items/Bows/EpicWoodBow.h"
#include "../Items/Bows/LegendaryMetalBow.h"
#include "../Items/Bows/LegendaryWoodBow.h"
#include "../Items/Bows/OrdinaryMetalBow.h"
#include "../Items/Bows/OrdinaryWoodBow.h"
#include "../Items/Characters/AIPlayer.h"
#include "../Items/Characters/Link.h"
#include "../Items/Effects/FireEffect.h"
#include "../Items/Effects/IceEffect.h"
#include "../Items/Effects/LightningEffect.h"
#include "../Items/LargeSwords/FireLargeSword.h"
#include "../Items/LargeSwords/IceLargeSword.h"
#include "../Items/LargeSwords/LightningLargeSword.h"
#include "../Items/LargeSwords/MetalLargeSword.h"
#include "../Items/LargeSwords/WoodLargeSword.h"
#include "../Items/Maps/Battlefield.h"
#include "../Items/Platforms/BronzePlatform.h"
#include "../Items/Platforms/SilverPlatform.h"
#include "../Items/Platforms/StonePlatform.h"
#include "../Items/Platforms/WoodPlatform.h"
#include "../Items/Spears/FireSpear.h"
#include "../Items/Spears/IceSpear.h"
#include "../Items/Spears/LightningSpear.h"
#include "../Items/Spears/MetalSpear.h"
#include "../Items/Spears/WoodSpear.h"
#include "../Items/Swords/FireSword.h"
#include "../Items/Swords/IceSword.h"
#include "../Items/Swords/LightningSword.h"
#include "../Items/Swords/MetalSword.h"
#include "../Items/Swords/WoodSword.h"

BattleScene::BattleScene(QObject* parent, const QString& gameMode) : Scene(parent), gameMode(gameMode)
{
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);
    map = new Battlefield();

    // initialize the cheat code input line edit
    cheatCodeInputLineEdit = new QLineEdit();
    cheatCodeInputLineEdit->setPlaceholderText("Enter The CheatCode Here...");
    cheatCodeLineEditProxy = this->addWidget(cheatCodeInputLineEdit);
    cheatCodeLineEditProxy->setPos(540, 700);
    cheatCodeLineEditProxy->setZValue(2);
    cheatCodeInputLineEdit->installEventFilter(this);

    // initialize the information area
    infoArea = new InformationArea(0, 0, 1280, 80);
    addItem(infoArea);

    // initialize the platforms
    platforms.append(new WoodPlatform());
    platforms[0]->setPos(0, 440);
    platforms.append(new StonePlatform());
    platforms[1]->setPos(1050, 440);
    platforms.append(new BronzePlatform());
    platforms[2]->setPos(320, 240);
    platforms.append(new SilverPlatform());
    platforms[3]->setPos(730, 240);

    // initialize the characters
    character[0] = new Link();
    character[0]->setTransform(QTransform().scale(-1, 1));
    character[0]->setToRight(true);
    if (gameMode == "PLAYER")
    {
        character[1] = new Link();
    }
    else if (gameMode == "AI")
    {
        character[1] = new AIPlayer();
    }
    character[1]->setToLeft(true);

    // add the items to the scene
    addItem(map);
    addItem(platforms[0]);
    addItem(platforms[1]);
    addItem(platforms[2]);
    addItem(platforms[3]);
    addItem(character[0]);
    addItem(character[1]);
    map->scaleToFitScene(this);
    character[0]->setPos(map->getSpawnPos() - QPointF(120, 0));
    character[1]->setPos(map->getSpawnPos() + QPointF(120, 0));
    for (auto platform : platforms)
    {
        qDebug() << "Top Border" << platform->getTopBorder() << "Bottom Border" << platform->getBottomBorder();
    }
}

void BattleScene::processInput()
{
    Scene::processInput();
    if (character[0] != nullptr)
    {
        character[0]->processInput();
    }
    if (character[1] != nullptr)
    {
        if (dynamic_cast<AIPlayer*>(character[1]) != nullptr)
        {
            processAIMoving(dynamic_cast<AIPlayer*>(character[1]));
        }
        character[1]->processInput();
    }
}

void BattleScene::processAIActions()
{
    if (auto ai = dynamic_cast<AIPlayer*>(character[1]); ai != nullptr)
    {
        if (ai->getState() == "IDLE")
        {
            if (ai->getCurrentWeapon() == nullptr)
            {
                for (auto weapon : spareWeapons)
                {
                    if (weapon->isMountable() == true && weapon->isMounted() == false)
                    {
                        ai->setApproachingState();
                        ai->target = weapon;
                        return;
                    }
                }
            }
            else if (ai->getUnusedWeapon() == nullptr)
            {
                if (ai->getCurrentWeapon() == ai->getMeleeWeapon())
                {
                    for (auto weapon : spareWeapons)
                    {
                        if (dynamic_cast<Bow*>(weapon) != nullptr && weapon->isMountable() == true && weapon->isMounted() == false)
                        {
                            ai->setApproachingState();
                            ai->target = weapon;
                            return;
                        }
                    }
                }
                else if (ai->getCurrentWeapon() == ai->getBow())
                {
                    for (auto weapon : spareWeapons)
                    {
                        if (dynamic_cast<MeleeWeapon*>(weapon) != nullptr && weapon->isMountable() == true && weapon->isMounted() == false)
                        {
                            ai->setApproachingState();
                            ai->target = weapon;
                            return;
                        }
                    }
                }
            }
            if (ai->getMeleeWeapon() != nullptr && ai->getMeleeWeapon()->damageType1->getDamageType() == "Ordinary")
            {
                for (auto weapon : spareWeapons)
                {
                    if (dynamic_cast<MeleeWeapon*>(weapon) != nullptr && weapon->isMountable() == true && weapon->isMounted() == false)
                    {
                        discardWeapon(ai);
                        ai->setApproachingState();
                        ai->target = weapon;
                        return;
                    }
                }
            }
            if (true)
            {
                for (auto weapon : spareWeapons)
                {
                    if (dynamic_cast<Arrow*>(weapon) != nullptr && weapon->isMountable() == true && weapon->isMounted() == false)
                    {
                        ai->setApproachingState();
                        ai->target = weapon;
                        return;
                    }
                }
            }
            if (ai->getArmorSuit()->proofType == "")
            {
                if (!spareArmorSuits.empty())
                {
                    ai->setApproachingState();
                    ai->target = spareArmorSuits[0];
                    return;
                }
            }
            if (ai->getCurrentWeapon() != nullptr)
            {
                if (ai->getCurrentWeapon() == ai->getMeleeWeapon() ||
                    ai->getCurrentWeapon() == ai->getBow() && ai->getCurrentArrow() != nullptr)
                {
                    ai->setApproachingState();
                    ai->target = character[0];
                    return;
                }
                if (ai->getCurrentWeapon() == ai->getBow() && ai->getCurrentArrow() == nullptr &&
                    ai->getUnusedWeapon() != nullptr)
                {
                    ai->switchWeapon();
                    ai->setApproachingState();
                    ai->target = character[0];
                    return;
                }
            }

        }
        else if (ai->getState() == "APPROACHING")
        {

        }
        else if (ai->getState() == "PICK_TARGET")
        {
            ai->setToLeft(ai->isToLeft());
            ai->setToRight(ai->isToRight());
            ai->setLeftDown(false);
            ai->setRightDown(false);
            ai->setIdleState();
            ai->target = nullptr;
            ai->setPickDown(false);
        }
        else if (ai->getState() == "ATTACK")
        {
            ai->setLeftDown(false);
            ai->setRightDown(false);
            if (ai->isUsingMelee())
            {
                if (!ai->isAttacking())
                {
                    ai->damageDone = false;
                }
                ai->setAttacking(true);
                ai->setIdleState();
            }
            else if (ai->isUsingBow() && ai->getCurrentArrow() != nullptr)
            {
                shootArrow(ai);
                ai->setIdleState();
            }
        }
    }
}

void BattleScene::processAIMoving(AIPlayer* aiPlayer)
{
    if (aiPlayer == nullptr || aiPlayer->target == nullptr)
    {
        return;
    }
    if (aiPlayer->state == "APPROACHING")
    {
        processAIApproach(aiPlayer);
    }
}

void BattleScene::processAIApproach(AIPlayer* aiPlayer)
{
    if (QLineF(aiPlayer->target->pos(),aiPlayer->pos()).length() <= 100)
    {
        if (dynamic_cast<Character*>(aiPlayer->target) != nullptr)
        {
            aiPlayer->setLeftDown(false);
            aiPlayer->setRightDown(false);
            aiPlayer->setAttackState();
        }
        else
        {
            aiPlayer->setPickTargetState();
            aiPlayer->setPickDown(true);
            return;
        }
    }
    // 当目标位于第三层，要先爬上第二层
    if (aiPlayer->target->y() <= 240)
    {
        if (aiPlayer->y() <= 240)
        {
            if (aiPlayer->target->x() > aiPlayer->x())
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
            else
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
        }
        else if (aiPlayer->y() <= 440)
        {
            if (aiPlayer->target->x() <= 640 && aiPlayer->isInAir() == false)
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
            else if (aiPlayer->target->x() >= 640 && aiPlayer->isInAir() == false)
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
            if (aiPlayer->isInAir() == false && (aiPlayer->x() >= 200 && aiPlayer->x() <= 230 || aiPlayer->x() <= 1080 && aiPlayer->x() >= 1050))
            {
                aiPlayer->startJumping();
            }
        }
        else if (aiPlayer->y() <= map->getFloorHeight())
        {
            if (aiPlayer->target->x() >= 640)
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
            else if (aiPlayer->target->x() <= 640)
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
            if (aiPlayer->isInAir() == false && (aiPlayer->x() <= 300 || aiPlayer->x() >= 980))
            {
                aiPlayer->startJumping();
            }
        }
    }
    else if (aiPlayer->target->y() <= 440)
    {
        if (aiPlayer->y() <= 240 && aiPlayer->isInAir() ==false)
        {
            if (aiPlayer->target->x() > aiPlayer->x())
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
            else if (aiPlayer->target->x() < aiPlayer->x())
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
        }
        if (aiPlayer->target->x() < aiPlayer->x())
        {
            aiPlayer->setLeftDown(true);
            aiPlayer->setRightDown(false);
        }
        else if (aiPlayer->target->x() > aiPlayer->x())
        {
            aiPlayer->setRightDown(true);
            aiPlayer->setLeftDown(false);
        }
        if (aiPlayer->isInAir() == false && (aiPlayer->x() >= 230 && aiPlayer->x() <= 260 || aiPlayer->x() <= 1050 && aiPlayer->x() >= 1020))
        {
            aiPlayer->startJumping();
        }
    }
    else
    {
        if (aiPlayer->y() <= 250)
        {
            if (aiPlayer->target->x() <= 640)
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
            else if (aiPlayer->target->x() >= 640)
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
        }
        else if (aiPlayer->y() <= 450 && aiPlayer->isInAir() == false)
        {
            if (aiPlayer->target->x() < aiPlayer->x())
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
            else if (aiPlayer->target->x() > aiPlayer->x())
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
        }
        else
        {
            if (aiPlayer->target->x() > aiPlayer->x() + 100)
            {
                aiPlayer->setRightDown(true);
                aiPlayer->setLeftDown(false);
            }
            else if (aiPlayer->target->x() < aiPlayer->x() - 100)
            {
                aiPlayer->setLeftDown(true);
                aiPlayer->setRightDown(false);
            }
        }
    }
    aiPlayer->pre_pos = aiPlayer->pos();
}

void BattleScene::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            character[0]->setLeftDown(true);
            character[0]->setToLeft(true);
        }
        break;
    case Qt::Key_D:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            character[0]->setRightDown(true);
            character[0]->setToRight(true);
        }
        break;
    case Qt::Key_F:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            character[0]->setPickDown(true);
        }
        break;
    case Qt::Key_W:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            if (!character[0]->isInAir())
            {
                character[0]->startJumping();
            }
        }
        break;
    case Qt::Key_E:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            if (character[0]->isUsingMelee())
            {
                discardWeapon(character[0]);
            }
            else if (character[0]->isUsingBow())
            {
                shootArrow(character[0]);
            }
        }
        break;
    case Qt::Key_R:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            character[0]->switchWeapon();
        }
        break;
    case Qt::Key_Q:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            if (character[0]->isUsingBow())
            {
                character[0]->switchArrow();
            }
            else if (character[0]->isUsingMelee())
            {
                if (!character[0]->isAttacking())
                {
                    character[0]->damageDone = false;
                }
                character[0]->setAttacking(true);
            }
        }
        break;
    case Qt::Key_T:
        if (character[0] != nullptr && dynamic_cast<IceEffect*>(character[0]->currentEffect) == nullptr)
        {
            if (character[0]->isUsingBow())
            {
                discardWeapon(character[0]);
            }
        }
        break;
    case Qt::Key_H:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->setLeftDown(true);
            character[1]->setToLeft(true);
        }
        break;
    case Qt::Key_K:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->setRightDown(true);
            character[1]->setToRight(true);
        }
        break;
    case Qt::Key_L:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->setPickDown(true);
        }
        break;
    case Qt::Key_U:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            if (!character[1]->isInAir())
            {
                character[1]->startJumping();
            }
        }
        break;
    case Qt::Key_I:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            if (character[1]->isUsingMelee())
            {
                discardWeapon(character[1]);
            }
            else if (character[1]->isUsingBow())
            {
                shootArrow(character[1]);
            }
        }
        break;
    case Qt::Key_O:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->switchWeapon();
        }
        break;
    case Qt::Key_Y:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            if (character[1]->isUsingBow())
            {
                character[1]->switchArrow();
            }
            else if (character[1]->isUsingMelee())
            {
                if (!character[1]->isAttacking())
                {
                    character[1]->damageDone = false;
                }
                character[1]->setAttacking(true);
            }
        }
        break;
    case Qt::Key_P:
        if (character[1] != nullptr && dynamic_cast<IceEffect*>(character[1]->currentEffect) == nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            if (character[1]->isUsingBow())
            {
                discardWeapon(character[1]);
            }
        }
        break;
    default:
        Scene::keyPressEvent(event);
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        if (character[0] != nullptr)
        {
            character[0]->setLeftDown(false);
        }
        break;
    case Qt::Key_D:
        if (character[0] != nullptr)
        {
            character[0]->setRightDown(false);
        }
        break;
    case Qt::Key_F:
        if (character[0] != nullptr)
        {
            character[0]->setPickDown(false);
        }
        break;
    case Qt::Key_H:
        if (character[1] != nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->setLeftDown(false);
        }
        break;
    case Qt::Key_K:
        if (character[1] != nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->setRightDown(false);
        }
        break;
    case Qt::Key_L:
        if (character[1] != nullptr && dynamic_cast<AIPlayer*>(character[1]) == nullptr)
        {
            character[1]->setPickDown(false);
        }
        break;
    default:
        Scene::keyReleaseEvent(event);
    }
}

void BattleScene::update()
{
    if (isGameOver == true)
    {
        // 当游戏结束时，进行倒计时，然后发送游戏结束信号
        gameOverUpdate();
    }
    else
    {
        // 当游戏未结束时，进行游戏的更新
        Scene::update();
        if (dynamic_cast<AIPlayer*>(character[1]) != nullptr)
        {
            processAIActions();
        }
        processLanding();
        processCollision();
        processAttacking();
        processHitting();
        processAnimationAfterHit();
        processEffect();
        processInformation();
        autoGenerateItems();
        endTheGame();
    }
}

void BattleScene::gameOverUpdate()
{
    if (gameOverCountdown > 0)
    {
        --gameOverCountdown;
    }
    else
    {
        if (character[0]->getHitPoints() > 0)
        {
            emit gameOver("Left Win");
        }
        else if (character[1]->getHitPoints() > 0)
        {
            emit gameOver("Right Win");
        }
    }
}

void BattleScene::processMovement()
{
    Scene::processMovement();
    for (const auto character : character)
    {
        if (character != nullptr)
        {
            // auto pos = character->pos();
            auto pos_to_go = character->pos() + character->getVelocity() * static_cast<double>(deltaTime);
            if (character->isInAir())
            {
                character->setVelocity(
                    character->getVelocity() + gravitationalAcceleration * static_cast<double>(deltaTime));
            }
            character->setPos(pos_to_go);
        }
    }
    for (const auto weapon : spareWeapons)
    {
        if (weapon != nullptr)
        {
            auto pos_to_go = weapon->pos() + weapon->getVelocity() * static_cast<double>(deltaTime);
            weapon->setPos(pos_to_go);
            if (weapon->isInAir())
            {
                weapon->setVelocity(weapon->getVelocity() + gravitationalAcceleration * static_cast<double>(deltaTime));
            }
        }
    }
    for (const auto armorSuit : spareArmorSuits)
    {
        if (armorSuit != nullptr)
        {
            auto pos_to_go = armorSuit->pos() + armorSuit->getVelocity() * static_cast<double>(deltaTime);
            armorSuit->setPos(pos_to_go);
            if (armorSuit->isInAir())
            {
                armorSuit->setVelocity(
                    armorSuit->getVelocity() + gravitationalAcceleration * static_cast<double>(deltaTime));
            }
        }
    }
}

void BattleScene::processPicking()
{
    Scene::processPicking();

    // Process picking of all mountable items.
    for (auto character : character)
    {
        if (character->isPicking())
        {
            if (auto mountable = findNearestUnmountedMountable(character->pos(), 100.); mountable != nullptr)
            {
                pickupMountable(character, mountable);
            }
        }
    }
}

void BattleScene::processLanding()
{
    // Judge if the characters is landing.
    for (const auto character : character)
    {
        if (character != nullptr)
        {
            character->setInAir(true);
            auto pos = character->pos();
            auto pre_pos = pos - 4 * character->getVelocity() * static_cast<double>(deltaTime);
            if (pos.y() >= map->getFloorHeight())
            {
                character->setInAir(false);
                auto velocity = character->getVelocity();
                velocity.setY(0);
                character->setVelocity(velocity);
                pos.setY(map->getFloorHeight());
                character->setPos(pos);
                continue;
            }
            for (const auto platform : platforms)
            {
                if (pos.x() <= platform->getRightBorder() && pos.x() >= platform->getLeftBorder() &&
                    pos.y() >= platform->getTopBorder() && pre_pos.y() <= platform->getTopBorder())
                {
                    character->setInAir(false);
                    auto velocity = character->getVelocity();
                    velocity.setY(0);
                    character->setVelocity(velocity);
                    pos.setY(platform->getTopBorder());
                    character->setPos(pos);
                    break;
                }
            }
        }
    }

    // Judge if the spare weapons is landing.
    for (const auto weapon : spareWeapons)
    {
        if (weapon != nullptr && weapon->isOnAttack() == false)
        {
            weapon->setInAir(true);
            auto pos = weapon->pos();
            auto pre_pos = pos - 4 * weapon->getVelocity() * static_cast<double>(deltaTime);
            if (pos.y() >= map->getFloorHeight())
            {
                weapon->setInAir(false);
                auto velocity = weapon->getVelocity();
                velocity.setY(0);
                weapon->setVelocity(velocity);
                pos.setY(map->getFloorHeight());
                weapon->setPos(pos);
                continue;
            }
            for (const auto platform : platforms)
            {
                if (pos.x() <= platform->getRightBorder() && pos.x() >= platform->getLeftBorder() &&
                    pos.y() >= platform->getTopBorder() && pre_pos.y() <= platform->getTopBorder())
                {
                    weapon->setInAir(false);
                    auto velocity = weapon->getVelocity();
                    velocity.setY(0);
                    weapon->setVelocity(velocity);
                    pos.setY(platform->getTopBorder());
                    weapon->setPos(pos);
                    break;
                }
            }
        }
    }

    // Judge if the spare armor suits is landing.
    for (const auto armorSuit : spareArmorSuits)
    {
        if (armorSuit != nullptr)
        {
            armorSuit->setInAir(true);
            auto pos = armorSuit->pos();
            auto pre_pos = pos - 4 * armorSuit->getVelocity() * static_cast<double>(deltaTime);
            if (pos.y() >= map->getFloorHeight())
            {
                armorSuit->setInAir(false);
                auto velocity = armorSuit->getVelocity();
                velocity.setY(0);
                armorSuit->setVelocity(velocity);
                pos.setY(map->getFloorHeight());
                armorSuit->setPos(pos);
                continue;
            }
            for (const auto platform : platforms)
            {
                if (pos.x() <= platform->getRightBorder() && pos.x() >= platform->getLeftBorder() &&
                    pos.y() >= platform->getTopBorder() && pre_pos.y() <= platform->getTopBorder())
                {
                    armorSuit->setInAir(false);
                    auto velocity = armorSuit->getVelocity();
                    velocity.setY(0);
                    armorSuit->setVelocity(velocity);
                    pos.setY(platform->getTopBorder());
                    armorSuit->setPos(pos);
                    break;
                }
            }
        }
    }
}

void BattleScene::processCollision()
{
    for (auto character : character)
    {
        if (character != nullptr)
        {
            auto pos = character->pos();
            auto pre_pos = pos - 4 * character->getVelocity() * static_cast<double>(deltaTime);

            // 判断边界
            if (character->isLeftDown() && pos.x() <= 0 && pre_pos.x() > 0)
            {
                pos.setX(0);
            }
            if (character->isRightDown() && pos.x() >= 1280 && pre_pos.x() < 1280)
            {
                pos.setX(1280);
            }

            // 判断与平台的碰撞
            for (const auto platform : platforms)
            {
                const auto top_height = pos.y() - 200;
                const auto pre_top_height = pre_pos.y() - 200;
                // 向左的碰撞检测
                if (character->isLeftDown() &&
                    pre_pos.x() >= platform->getRightBorder() && pos.x() < platform->getRightBorder() &&
                    character->getTopHeight() < platform->getBottomBorder() && character->getBottomHeight() > platform->
                    getTopBorder())
                {
                    pos.setX(platform->getRightBorder());
                }
                //向右的碰撞检测
                if (character->isRightDown() &&
                    pre_pos.x() <= platform->getLeftBorder() && pos.x() > platform->getLeftBorder() &&
                    character->getTopHeight() < platform->getBottomBorder() && character->getBottomHeight() > platform->
                    getTopBorder())
                {
                    pos.setX(platform->getLeftBorder());
                }
                //向上的碰撞检测
                if (character->getVelocity().y() < 0 &&
                    pre_top_height >= platform->getBottomBorder() && top_height < platform->getBottomBorder() &&
                    pos.x() < platform->getRightBorder() && pos.x() > platform->getLeftBorder())
                {
                    pos.setY(platform->getBottomBorder() + 200);
                    auto velocity = character->getVelocity();
                    // velocity.setY(-velocity.y());
                    velocity.setY(0);
                    character->setVelocity(velocity);
                }
            }
            character->setPos(pos);
        }
    }
}

Mountable* BattleScene::findNearestUnmountedMountable(const QPointF& pos, qreal distance_threshold)
{
    Mountable* nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem* item : items())
    {
        if (auto mountable = dynamic_cast<Mountable*>(item))
        {
            if (!mountable->isMounted() && mountable->isMountable())
            {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance)
                {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }
    return nearest;
}

Mountable* BattleScene::pickupMountable(Character* character, Mountable* mountable)
{
    // pick up weapon
    if (auto weapon = dynamic_cast<Weapon*>(mountable))
    {
        if (dynamic_cast<MeleeWeapon*>(weapon) || dynamic_cast<Bow*>(weapon))
        {
            character->pickupWeapon(weapon);
            for (auto itr = spareWeapons.begin(); itr != spareWeapons.end(); ++itr)
            {
                if (*itr == weapon)
                {
                    spareWeapons.erase(itr);
                    break;
                }
            }
        }

        // pick up arrow
        if (dynamic_cast<Arrow*>(weapon))
        {
            character->pickupArrow(dynamic_cast<Arrow*>(weapon));
            for (auto itr = spareWeapons.begin(); itr != spareWeapons.end(); ++itr)
            {
                if (weapon == *itr)
                {
                    spareWeapons.erase(itr);
                    break;
                }
            }
            delete weapon;
            weapon = nullptr;
            return nullptr;
        }
    }

    // pick up armor suit
    if (const auto armorSuit = dynamic_cast<ArmorSuit*>(mountable))
    {
        character->pickupArmorSuit(armorSuit);
        for (auto itr = spareArmorSuits.begin(); itr != spareArmorSuits.end(); ++itr)
        {
            if (*itr == armorSuit)
            {
                spareArmorSuits.erase(itr);
                break;;
            }
        }
    }
    return nullptr;
}

void BattleScene::discardWeapon(Character* character)
{
    if (const auto onAttackMeleeWeapon = character->discardWeapon(); onAttackMeleeWeapon != nullptr)
    {
        onAttackMeleeWeapon->setMountable(false);
        onAttackMeleeWeapon->setOnAttack(true);
        spareWeapons.push_back(onAttackMeleeWeapon);
    }
}

void BattleScene::shootArrow(Character* character)
{
    auto onAttackArrows = character->shootArrow();
    if (!onAttackArrows.empty())
    {
        for (auto arrow : onAttackArrows)
        {
            if (arrow != nullptr)
            {
                arrow->setMountable(false);
                arrow->setOnAttack(true);
                addItem(arrow);
                spareWeapons.push_back(arrow);
            }
        }
    }
}

void BattleScene::autoGenerateItems()
{
    // Generate weapons automatically.
    if (const auto randomNumber = QRandomGenerator::global()->bounded(12000); randomNumber < 28)
    {
        Weapon* newWeapon = nullptr;
        ArmorSuit* newArmorSuit = nullptr;
        switch (randomNumber)
        {
        case 0:
            newWeapon = new WoodSword();
            break;
        case 1:
            newWeapon = new MetalSword();
            break;
        case 2:
            newWeapon = new FireSword();
            break;
        case 3:
            newWeapon = new IceSword();
            break;
        case 4:
            newWeapon = new LightningSword();
            break;
        case 5:
            newWeapon = new WoodLargeSword();
            break;
        case 6:
            newWeapon = new MetalLargeSword();
            break;
        case 7:
            newWeapon = new FireLargeSword();
            break;
        case 8:
            newWeapon = new IceLargeSword();
            break;
        case 9:
            newWeapon = new LightningLargeSword();
            break;
        case 10:
            newWeapon = new WoodSpear();
            break;
        case 11:
            newWeapon = new MetalSpear();
            break;
        case 12:
            newWeapon = new FireSpear();
            break;
        case 13:
            newWeapon = new IceSpear();
            break;
        case 14:
            newWeapon = new LightningSpear();
            break;
        case 15:
            newWeapon = new OrdinaryWoodBow();
            break;
        case 16:
            newWeapon = new OrdinaryMetalBow();
            break;
        case 17:
            newWeapon = new LegendaryWoodBow();
            break;
        case 18:
            newWeapon = new LegendaryMetalBow();
            break;
        case 19:
            newWeapon = new EpicWoodBow();
            break;
        case 20:
            newWeapon = new EpicMetalBow();
            break;
        case 21:
            newArmorSuit = new FireProofArmorSuit();
            break;
        case 22:
            newArmorSuit = new ColdProofArmorSuit();
            break;
        case 23:
            newArmorSuit = new LightningProofArmorSuit();
            break;
        case 24:
            newWeapon = new OrdinaryArrow();
            break;
        case 25:
            newWeapon = new FireArrow();
            break;
        case 26:
            newWeapon = new IceArrow();
            break;
        case 27:
            newWeapon = new LightningArrow();
            break;
        default:
            break;
        }
        if (newWeapon != nullptr)
        {
            newWeapon->unmount();
            addItem(newWeapon);
            const int x = QRandomGenerator::global()->bounded(1280);
            newWeapon->setPos(x, 0);
            spareWeapons.push_back(newWeapon);
        }
        if (newArmorSuit != nullptr)
        {
            newArmorSuit->unmount();
            addItem(newArmorSuit);
            const int x = QRandomGenerator::global()->bounded(1280);
            newArmorSuit->setPos(x, 0);
            spareArmorSuits.push_back(newArmorSuit);
        }
    }
}

bool BattleScene::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == cheatCodeInputLineEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            auto* keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                processCheatCode(cheatCodeInputLineEdit->text());
                cheatCodeInputLineEdit->clear();
                return true;
            }
            return Scene::eventFilter(watched, event);
        }
        return Scene::eventFilter(watched, event);
    }
    return Scene::eventFilter(watched, event);
}

void BattleScene::endTheGame()
{
    if (character[0]->getHitPoints() <= 0 || character[1]->getHitPoints() <= 0)
    {
        isGameOver = true;
    }
}

QVector<Platform*> BattleScene::get_platforms() const
{
    return platforms;
}

QString BattleScene::get_game_mode() const
{
    return gameMode;
}

void BattleScene::processCheatCode(const QString& cheatCode)
{
    if (cheatCode.size() != 4)
    {
        return;
    }
    if (cheatCode.left(3) == "ARM")
    {
        ArmorSuit* newArmorSuit = nullptr;
        if (cheatCode[3] == 'F')
        {
            newArmorSuit = new FireProofArmorSuit();
        }
        if (cheatCode[3] == 'I')
        {
            newArmorSuit = new ColdProofArmorSuit();
        }
        if (cheatCode[3] == 'L')
        {
            newArmorSuit = new LightningProofArmorSuit();
        }
        if (newArmorSuit != nullptr)
        {
            newArmorSuit->unmount();
            addItem(newArmorSuit);
            const int x = QRandomGenerator::global()->bounded(1280);
            newArmorSuit->setPos(x, 0);
            spareArmorSuits.push_back(newArmorSuit);
        }
    }
    if (cheatCode.left(3) == "SWO")
    {
        Sword* newSword = nullptr;
        if (cheatCode[3] == 'F')
        {
            newSword = new FireSword();
        }
        if (cheatCode[3] == 'I')
        {
            newSword = new IceSword();
        }
        if (cheatCode[3] == 'L')
        {
            newSword = new LightningSword();
        }
        if (cheatCode[3] == 'W')
        {
            newSword = new WoodSword();
        }
        if (cheatCode[3] == 'M')
        {
            newSword = new MetalSword();
        }
        if (newSword != nullptr)
        {
            newSword->unmount();
            addItem(newSword);
            const int x = QRandomGenerator::global()->bounded(1280);
            newSword->setPos(x, 0);
            spareWeapons.push_back(newSword);
        }
    }
    if (cheatCode.left(3) == "LSW")
    {
        LargeSword* newLsw = nullptr;
        if (cheatCode[3] == 'F')
        {
            newLsw = new FireLargeSword();
        }
        if (cheatCode[3] == 'I')
        {
            newLsw = new IceLargeSword();
        }
        if (cheatCode[3] == 'L')
        {
            newLsw = new LightningLargeSword();
        }
        if (cheatCode[3] == 'W')
        {
            newLsw = new WoodLargeSword();
        }
        if (cheatCode[3] == 'M')
        {
            newLsw = new MetalLargeSword();
        }
        if (newLsw != nullptr)
        {
            newLsw->unmount();
            addItem(newLsw);
            const int x = QRandomGenerator::global()->bounded(1280);
            newLsw->setPos(x, 0);
            spareWeapons.push_back(newLsw);
        }
    }
    if (cheatCode.left(3) == "SPE")
    {
        Spear* newSpear = nullptr;
        if (cheatCode[3] == 'F')
        {
            newSpear = new FireSpear();
        }
        if (cheatCode[3] == 'I')
        {
            newSpear = new IceSpear();
        }
        if (cheatCode[3] == 'L')
        {
            newSpear = new LightningSpear();
        }
        if (cheatCode[3] == 'W')
        {
            newSpear = new WoodSpear();
        }
        if (cheatCode[3] == 'M')
        {
            newSpear = new MetalSpear();
        }
        if (newSpear != nullptr)
        {
            newSpear->unmount();
            addItem(newSpear);
            const int x = QRandomGenerator::global()->bounded(1280);
            newSpear->setPos(x, 0);
            spareWeapons.push_back(newSpear);
        }
    }
    if (cheatCode.left(3) == "BOW")
    {
        Bow* newBow = nullptr;
        if (cheatCode[3] == '1')
        {
            newBow = new OrdinaryWoodBow();
        }
        if (cheatCode[3] == '2')
        {
            newBow = new OrdinaryMetalBow();
        }
        if (cheatCode[3] == '3')
        {
            newBow = new LegendaryWoodBow();
        }
        if (cheatCode[3] == '4')
        {
            newBow = new LegendaryMetalBow();
        }
        if (cheatCode[3] == '5')
        {
            newBow = new EpicWoodBow();
        }
        if (cheatCode[3] == '6')
        {
            newBow = new EpicMetalBow();
        }
        if (newBow != nullptr)
        {
            newBow->unmount();
            addItem(newBow);
            const int x = QRandomGenerator::global()->bounded(1280);
            newBow->setPos(x, 0);
            spareWeapons.push_back(newBow);
        }
    }
    if (cheatCode.left(3) == "ARR")
    {
        Arrow* newArrow = nullptr;
        if (cheatCode[3] == 'O')
        {
            newArrow = new OrdinaryArrow();
        }
        if (cheatCode[3] == 'F')
        {
            newArrow = new FireArrow();
        }
        if (cheatCode[3] == 'I')
        {
            newArrow = new IceArrow();
        }
        if (cheatCode[3] == 'L')
        {
            newArrow = new LightningArrow();
        }
        if (newArrow != nullptr)
        {
            newArrow->unmount();
            addItem(newArrow);
            const int x = QRandomGenerator::global()->bounded(1280);
            newArrow->setPos(x, 0);
            spareWeapons.push_back(newArrow);
        }
    }
}

void BattleScene::processAttacking()
{
    if (character[0] != nullptr)
    {
        character[0]->processAttacking();
        if (character[0]->isAttacking() && character[0]->damageDone == false)
        {
            if (character[1] != nullptr)
            {
                auto rela_pos = character[0]->getCurrentWeapon()->pos();
                if (character[0]->isToRight())
                {
                    rela_pos.setX(-rela_pos.x());
                }
                auto pos = character[0]->pos() + rela_pos;
                // qDebug() << "current weapon pos: " << pos;

                if (pos.y() > character[1]->getTopHeight() && pos.y() - 100 < character[1]->getBottomHeight()
                    && pos.x() - 50 < character[1]->pos().x() && pos.x() + 50 > character[1]->pos().x())
                {
                    // character[1]->setHitPoints(character[1]->getHitPoints() - 10);
                    if (character[0]->getCurrentWeapon()->damageType1->getDamageType() != character[1]->getArmorSuit()->
                        proofType)
                    {
                        character[1]->processDamage(character[0]->getCurrentWeapon()->get_damage());
                        character[1]->beHit = true;
                        character[0]->damageDone = true;
                        addEffect(character[0]->getCurrentWeapon(), character[1]);
                    }
                    // qDebug() << "HitPoints: " << character[1]->getHitPoints();
                }

                if (dynamic_cast<LargeSword*>(character[0]->getCurrentWeapon()) != nullptr && character[0]->damageDone
                    == false)
                {
                    auto back_rela_pos = QPointF(-rela_pos.x(), rela_pos.y());
                    auto back_pos = character[0]->pos() + back_rela_pos;
                    // qDebug() << "backward weapon pos: " << back_pos;
                    if (back_pos.y() > character[1]->getTopHeight() && back_pos.y() - 100 < character[1]->
                        getBottomHeight()
                        && back_pos.x() - 50 < character[1]->pos().x() && back_pos.x() + 50 > character[1]->pos().x())
                    {
                        // character[1]->setHitPoints(character[1]->getHitPoints() - 10);
                        if (character[0]->getCurrentWeapon()->damageType1->getDamageType() != character[1]->
                            getArmorSuit()->proofType)
                        {
                            character[1]->processDamage(character[0]->getCurrentWeapon()->get_damage());
                            character[1]->beHit = true;
                            character[0]->damageDone = true;
                            addEffect(character[0]->getCurrentWeapon(), character[1]);
                        }
                        // qDebug() << "HitPoints: " << character[1]->getHitPoints();
                    }
                }
            }
        }
    }
    if (character[1] != nullptr)
    {
        character[1]->processAttacking();
        if (character[1]->isAttacking() && character[1]->damageDone == false)
        {
            if (character[0] != nullptr)
            {
                auto rela_pos = character[1]->getCurrentWeapon()->pos();
                if (character[1]->isToRight())
                {
                    rela_pos.setX(-rela_pos.x());
                }
                auto pos = character[1]->pos() + rela_pos;
                // qDebug() << "current weapon pos: " << pos;

                if (pos.y() > character[0]->getTopHeight() && pos.y() - 100 < character[0]->getBottomHeight()
                    && pos.x() - 50 < character[0]->pos().x() && pos.x() + 50 > character[0]->pos().x())
                {
                    // character[0]->setHitPoints(character[0]->getHitPoints() - 10);
                    if (character[1]->getCurrentWeapon()->damageType1->getDamageType() != character[0]->getArmorSuit()->
                        proofType)
                    {
                        character[0]->processDamage(character[1]->getCurrentWeapon()->get_damage());
                        character[0]->beHit = true;
                        character[1]->damageDone = true;
                        addEffect(character[1]->getCurrentWeapon(), character[0]);
                    }
                    // qDebug() << "Character[0] HitPoints: " << character[0]->getHitPoints();
                }

                if (dynamic_cast<LargeSword*>(character[1]->getCurrentWeapon()) != nullptr && character[1]->damageDone
                    == false)
                {
                    auto back_rela_pos = QPointF(-rela_pos.x(), rela_pos.y());
                    auto back_pos = character[1]->pos() + back_rela_pos;
                    // qDebug() << "backward weapon pos: " << back_pos;
                    if (back_pos.y() > character[0]->getTopHeight() && back_pos.y() - 100 < character[0]->
                        getBottomHeight()
                        && back_pos.x() - 50 < character[0]->pos().x() && back_pos.x() + 50 > character[0]->pos().x())
                    {
                        // character[0]->setHitPoints(character[0]->getHitPoints() - 10);
                        if (character[1]->getCurrentWeapon()->damageType1->getDamageType() != character[0]->
                            getArmorSuit()->proofType)
                        {
                            character[0]->processDamage(character[1]->getCurrentWeapon()->get_damage());
                            character[0]->beHit = true;
                            character[1]->damageDone = true;
                            addEffect(character[1]->getCurrentWeapon(), character[0]);
                        }
                        // qDebug() << "HitPoints: " << character[0]->getHitPoints();
                    }
                }
            }
        }
    }
}

void BattleScene::processAnimationAfterHit()
{
    for (auto character : character)
    {
        if (character != nullptr)
        {
            character->displayHit();
        }
    }
}

void BattleScene::processHitting()
{
    for (auto& spareWeapon : spareWeapons)
    {
        if (spareWeapon != nullptr && spareWeapon->isOnAttack() == true)
        {
            qDebug() << "OnAttack";
            auto pos = spareWeapon->pos();
            auto velocity = spareWeapon->getVelocity();
            auto pre_pos = pos - velocity * static_cast<double>(deltaTime);

            // 判断是否击中地面
            if (pos.y() >= map->getFloorHeight() && pre_pos.y() < map->getFloorHeight())
            {
                for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                {
                    if (*itr == spareWeapon)
                    {
                        effectedItems.erase(itr);
                        break;
                    }
                }
                for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                {
                    if (*itr == spareWeapon)
                    {
                        toBeEffectedItems.erase(itr);
                        break;
                    }
                }
                delete spareWeapon;
                spareWeapon = nullptr;
                qDebug() << "Hit The Ground";
            }

            if (spareWeapon == nullptr)
            {
                continue;
            }

            // 判断是否击中平台
            for (auto platform : platforms)
            {
                if (platform != nullptr)
                {
                    if (velocity.x() >= 0)
                    {
                        if (pos.x() + 50 >= platform->getLeftBorder() && pre_pos.x() + 50 < platform->getLeftBorder() &&
                            pos.y() > platform->getTopBorder() && pos.y() - 100 < platform->getBottomBorder())
                        {
                            addEffect(spareWeapon, platform);
                            for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    effectedItems.erase(itr);
                                    break;
                                }
                            }
                            for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    toBeEffectedItems.erase(itr);
                                    break;
                                }
                            }
                            delete spareWeapon;
                            spareWeapon = nullptr;
                            qDebug() << "Hit Platform From Left";
                            break;;
                        }
                    }
                    else if (velocity.x() < 0)
                    {
                        if (pos.x() - 50 <= platform->getRightBorder() && pre_pos.x() - 50 > platform->getLeftBorder()
                            &&
                            pos.y() > platform->getTopBorder() && pos.y() - 100 < platform->getBottomBorder())
                        {
                            addEffect(spareWeapon, platform);
                            for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    effectedItems.erase(itr);
                                    break;
                                }
                            }
                            for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    toBeEffectedItems.erase(itr);
                                    break;
                                }
                            }
                            delete spareWeapon;
                            spareWeapon = nullptr;
                            qDebug() << "Hit Platform From Right";
                            break;
                        }
                    }
                    if (velocity.y() >= 0)
                    {
                        if (pos.y() >= platform->getTopBorder() && pre_pos.y() < platform->getTopBorder() &&
                            pos.x() > platform->getLeftBorder() && pos.x() < platform->getRightBorder())
                        {
                            addEffect(spareWeapon, platform);
                            for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    effectedItems.erase(itr);
                                    break;
                                }
                            }
                            for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    toBeEffectedItems.erase(itr);
                                    break;
                                }
                            }
                            delete spareWeapon;
                            spareWeapon = nullptr;
                            qDebug() << "Hit Platform From Above";
                            break;
                        }
                    }
                }
            }

            if (spareWeapon == nullptr)
            {
                continue;
            }

            // 判断是否击中对手
            for (auto character : character)
            {
                if (character != nullptr && character != spareWeapon->getHolder())
                {
                    if (velocity.x() >= 0)
                    {
                        if (pos.x() + 50 >= character->x() && pre_pos.x() + 50 < character->x() &&
                            pos.y() > character->getTopHeight() && pos.y() - 100 < character->getBottomHeight())
                        {
                            if (spareWeapon->damageType1->getDamageType() != character->getArmorSuit()->proofType)
                            {
                                character->beHit = true;
                                character->processDamage(spareWeapon->get_damage());
                                addEffect(spareWeapon, character);
                            }
                            for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    effectedItems.erase(itr);
                                    break;
                                }
                            }
                            for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    toBeEffectedItems.erase(itr);
                                    break;
                                }
                            }
                            delete spareWeapon;
                            spareWeapon = nullptr;
                            // character->setHitPoints(character->getHitPoints() - 10);
                            break;
                        }
                    }
                    else if (velocity.x() < 0)
                    {
                        if (pos.x() - 50 <= character->x() && pre_pos.x() + 50 > character->x() &&
                            pos.y() > character->getTopHeight() && pos.y() - 100 < character->getBottomHeight())
                        {
                            if (spareWeapon->damageType1->getDamageType() != character->getArmorSuit()->proofType)
                            {
                                character->beHit = true;
                                character->processDamage(spareWeapon->get_damage());
                                addEffect(spareWeapon, character);
                            }
                            for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    effectedItems.erase(itr);
                                    break;
                                }
                            }
                            for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    toBeEffectedItems.erase(itr);
                                    break;
                                }
                            }
                            delete spareWeapon;
                            spareWeapon = nullptr;
                            // character->setHitPoints(character->getHitPoints() - 10);
                            break;
                        }
                    }
                    else if (velocity.y() >= 0)
                    {
                        if (pos.y() >= character->getTopHeight() && pre_pos.y() < character->getTopHeight() &&
                            pos.x() - 50 <= character->x() + 50 && pos.x() + 50 > character->x() - 50)
                        {
                            if (spareWeapon->damageType1->getDamageType() != character->getArmorSuit()->proofType)
                            {
                                character->beHit = true;
                                character->processDamage(spareWeapon->get_damage());
                                addEffect(spareWeapon, character);
                            }
                            for (auto itr =effectedItems.begin(); itr != effectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    effectedItems.erase(itr);
                                    break;
                                }
                            }
                            for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end(); ++itr)
                            {
                                if (*itr == spareWeapon)
                                {
                                    toBeEffectedItems.erase(itr);
                                    break;
                                }
                            }
                            delete spareWeapon;
                            spareWeapon = nullptr;
                            // character->setHitPoints(character->getHitPoints() - 10);
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto itr = spareWeapons.begin(); itr != spareWeapons.end();)
    {
        if (*itr == nullptr)
        {
            itr = spareWeapons.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}

void BattleScene::addEffect(Weapon* weapon, Item* item)
{
    // 物体不能重复叠加状态
    if (item->currentEffect != nullptr)
    {
        return;
    }

    auto damageType = weapon->damageType1->getDamageType();

    // 普通的伤害不造成任何效果
    if (damageType == "Ordinary")
    {
        return;
    }

    // 给人物加上元素附着
    if (auto character = dynamic_cast<Character*>(item); character != nullptr)
    {
        if (damageType == "Ordinary")
        {
            return;
        }
        if (damageType == "Fire")
        {
            auto flame1 = new FireEffect(character);
            auto flame2 = new FireEffect(character);
            auto flame3 = new FireEffect(character);
            flame1->setPos(-20, -160);
            flame2->setPos(-40, -170);
            flame3->setPos(-40, -140);
            character->effects.push_back(flame1);
            character->effects.push_back(flame2);
            character->effects.push_back(flame3);
            character->currentEffect = character->effects[0];
            effectedItems.push_back(character);
            spreadEffect(flame1, character->getCurrentWeapon());
            spreadEffect(flame1, character->getUnusedWeapon());
        }
        else if (damageType == "Ice")
        {
            auto ice = new IceEffect(character);
            ice->setPos(-40, -160);
            character->effects.push_back(ice);
            character->currentEffect = character->effects[0];
            effectedItems.push_back(character);
        }
        else if (damageType == "Lightning")
        {
            auto lightning = new LightningEffect(character);
            lightning->setPos(-40, -160);
            character->effects.push_back(lightning);
            character->currentEffect = character->effects[0];
            effectedItems.push_back(character);
            spreadEffect(lightning, character->getCurrentWeapon());
            spreadEffect(lightning, character->getUnusedWeapon());
        }
    }

    // 给平台加上元素附着
    if (auto platform = dynamic_cast<Platform*>(item); platform != nullptr)
    {
        qDebug() << "Process The Effect On Platform";
        if (damageType == "Ordinary")
        {
            return;
        }
        if (damageType == "Ice")
        {
        }
        if (damageType == "Fire" && platform->material->isWood())
        {
            auto flame1 = new FireEffect(platform);
            auto flame2 = new FireEffect(platform);
            auto flame3 = new FireEffect(platform);
            auto flame4 = new FireEffect(platform);
            flame1->setPos(0, 0);
            flame2->setPos(11.5, 0);
            flame3->setPos(23, 0);
            flame4->setPos(34.5, 0);
            flame1->setScale(0.04);
            flame2->setScale(0.04);
            flame3->setScale(0.04);
            flame4->setScale(0.04);
            platform->effects.push_back(flame1);
            platform->effects.push_back(flame2);
            platform->effects.push_back(flame3);
            platform->effects.push_back(flame4);
            platform->currentEffect = platform->effects[0];
            effectedItems.push_back(platform);
        }
        else if (damageType == "Lightning" && platform->material->isMetal())
        {
            auto lightning1 = new LightningEffect(platform);
            auto lightning2 = new LightningEffect(platform);
            auto lightning3 = new LightningEffect(platform);
            auto lightning4 = new LightningEffect(platform);
            lightning1->setPos(0, -0);
            lightning2->setPos(11.5, 0);
            lightning3->setPos(23, 0);
            lightning4->setPos(34.5, 0);
            lightning1->setScale(0.16);
            lightning2->setScale(0.16);
            lightning3->setScale(0.16);
            lightning4->setScale(0.16);
            platform->effects.push_back(lightning1);
            platform->effects.push_back(lightning2);
            platform->effects.push_back(lightning3);
            platform->effects.push_back(lightning4);
            platform->currentEffect = platform->effects[0];
            effectedItems.push_back(platform);
        }
    }
}

void BattleScene::spreadEffect(Effect* effect, Item* item)
{
    if (item == nullptr || effect == nullptr)
    {
        return;
    }

    if (item->currentEffect != nullptr)
    {
        return;
    }

    // 给武器加上元素附着
    if (auto weapon = dynamic_cast<Weapon*>(item); weapon != nullptr)
    {
        if (effect->type == "Fire" && weapon->material->isWood() == true)
        {
            if (dynamic_cast<Bow*>(weapon) != nullptr)
            {
                auto flame = new FireEffect(weapon);
                flame->setScale(0.2);
                flame->setPos(-30, -85);
                flame->setVisible(false);
                weapon->effects.push_back(flame);
                weapon->currentEffect = weapon->effects[0];
                toBeEffectedItems.push_back(weapon);
            }
            else if (dynamic_cast<Sword*>(weapon) != nullptr)
            {
                auto flame1 = new FireEffect(weapon);
                auto flame2 = new FireEffect(weapon);
                flame1->setScale(0.1);
                flame2->setScale(0.1);
                flame1->setPos(10, -70);
                flame2->setPos(-10, -50);
                flame1->setVisible(false);
                flame2->setVisible(false);
                weapon->effects.push_back(flame1);
                weapon->effects.push_back(flame2);
                weapon->currentEffect = weapon->effects[0];
                toBeEffectedItems.push_back(weapon);
            }
            else if (dynamic_cast<LargeSword*>(weapon) != nullptr)
            {
                auto flame = new FireEffect(weapon);
                flame->setScale(0.2);
                flame->setPos(0, -75);
                flame->setVisible(false);
                weapon->effects.push_back(flame);
                weapon->currentEffect = weapon->effects[0];
                toBeEffectedItems.push_back(weapon);
            }
            else if (dynamic_cast<Spear*>(weapon) != nullptr)
            {
                auto flame = new FireEffect(weapon);
                flame->setScale(0.1);
                flame->setPos(10, -80);
                flame->setVisible(false);
                weapon->effects.push_back(flame);
                weapon->currentEffect = weapon->effects[0];
                toBeEffectedItems.push_back(weapon);
            }
        }
        else if (effect->type == "Lightning" && weapon->material->isMetal() == true)
        {
            if (dynamic_cast<Bow*>(weapon) != nullptr)
            {
                auto lightning = new LightningEffect(weapon);
                lightning->setScale(0.8);
                lightning->setPos(-30, -85);
                weapon->effects.push_back(lightning);
                weapon->currentEffect = weapon->effects[0];
                weapon->currentEffect->countdown = effect->countdown - 1;
                toBeEffectedItems.push_back(weapon);
            }
            else if (dynamic_cast<Sword*>(weapon) != nullptr)
            {
                auto lightning1 = new LightningEffect(weapon);
                auto lightning2 = new LightningEffect(weapon);
                lightning1->setScale(0.4);
                lightning2->setScale(0.4);
                lightning1->setPos(10, -70);
                lightning2->setPos(-10, -45);
                weapon->effects.push_back(lightning1);
                weapon->effects.push_back(lightning2);
                weapon->currentEffect = weapon->effects[0];
                weapon->currentEffect->countdown = effect->countdown - 1;
                toBeEffectedItems.push_back(weapon);
            }
            else if (dynamic_cast<LargeSword*>(weapon) != nullptr)
            {
                effect->countdown += 1;
                auto lightning = new LightningEffect(weapon);
                lightning->setScale(0.8);
                lightning->setPos(0, -75);
                weapon->effects.push_back(lightning);
                weapon->currentEffect = weapon->effects[0];
                weapon->currentEffect->countdown = effect->countdown - 1;
                toBeEffectedItems.push_back(weapon);
            }
            else if (dynamic_cast<Spear*>(weapon) != nullptr)
            {
                auto lightning = new LightningEffect(weapon);
                lightning->setScale(0.4);
                lightning->setPos(10, -75);
                weapon->effects.push_back(lightning);
                weapon->currentEffect = weapon->effects[0];
                weapon->currentEffect->countdown = effect->countdown - 1;
                toBeEffectedItems.push_back(weapon);
            }
            if (weapon->isMounted() && weapon->isEquipped())
            {
                for (auto character : character)
                {
                    if (character->getCurrentWeapon() == weapon)
                    {
                        if (const auto fallenWeapon = character->discardWeapon(); fallenWeapon != nullptr)
                        {
                            fallenWeapon->setMountable(true);
                            fallenWeapon->setOnAttack(false);
                            fallenWeapon->setVelocity(QPointF(0, 0));
                            spareWeapons.push_back(fallenWeapon);
                        }
                    }
                }
            }
        }
    }

    // 给平台加上元素附着
    if (auto platform = dynamic_cast<Platform*>(item); platform != nullptr)
    {
        if (effect->type == "Fire" && platform->material->isWood() == true)
        {
            auto flame1 = new FireEffect(platform);
            auto flame2 = new FireEffect(platform);
            auto flame3 = new FireEffect(platform);
            auto flame4 = new FireEffect(platform);
            flame1->setPos(0, 0);
            flame2->setPos(11.5, 0);
            flame3->setPos(23, 0);
            flame4->setPos(34.5, 0);
            flame1->setScale(0.04);
            flame2->setScale(0.04);
            flame3->setScale(0.04);
            flame4->setScale(0.04);
            flame1->setVisible(false);
            flame2->setVisible(false);
            flame3->setVisible(false);
            flame4->setVisible(false);
            platform->effects.push_back(flame1);
            platform->effects.push_back(flame2);
            platform->effects.push_back(flame3);
            platform->effects.push_back(flame4);
            platform->currentEffect = platform->effects[0];
            toBeEffectedItems.push_back(platform);
        }
        else if (effect->type == "Lightning" && platform->material->isMetal() == true)
        {
            auto lightning1 = new LightningEffect(platform);
            auto lightning2 = new LightningEffect(platform);
            auto lightning3 = new LightningEffect(platform);
            auto lightning4 = new LightningEffect(platform);
            lightning1->setPos(0, -0);
            lightning2->setPos(11.5, 0);
            lightning3->setPos(23, 0);
            lightning4->setPos(34.5, 0);
            lightning1->setScale(0.16);
            lightning2->setScale(0.16);
            lightning3->setScale(0.16);
            lightning4->setScale(0.16);
            platform->effects.push_back(lightning1);
            platform->effects.push_back(lightning2);
            platform->effects.push_back(lightning3);
            platform->effects.push_back(lightning4);
            platform->currentEffect = platform->effects[0];
            platform->currentEffect->countdown = effect->countdown - 1;
            toBeEffectedItems.push_back(platform);
        }
    }

    // 给角色加上元素附着
    if (auto character = dynamic_cast<Character*>(item); character != nullptr)
    {
        if (effect->type == "Fire")
        {
            auto flame1 = new FireEffect(character);
            auto flame2 = new FireEffect(character);
            auto flame3 = new FireEffect(character);
            flame1->setPos(-20, -160);
            flame2->setPos(-40, -170);
            flame3->setPos(-40, -140);
            flame1->setVisible(false);
            flame2->setVisible(false);
            flame3->setVisible(false);
            character->effects.push_back(flame1);
            character->effects.push_back(flame2);
            character->effects.push_back(flame3);
            character->currentEffect = character->effects[0];
            toBeEffectedItems.push_back(character);
        }
        else if (effect->type == "Lightning")
        {
            auto lightning = new LightningEffect(character);
            lightning->setPos(-40, -160);
            character->effects.push_back(lightning);
            character->currentEffect = character->effects[0];
            character->currentEffect->countdown = effect->countdown - 1;
            toBeEffectedItems.push_back(character);
        }
    }
}

void BattleScene::processEffect()
{
    // 将被传播的受元素影响的物体加入
    for (auto itr = toBeEffectedItems.begin(); itr != toBeEffectedItems.end();)
    {
        if (*itr != nullptr && (*itr)->currentEffect != nullptr)
        {
            // 对于火元素，需经过一段时间后再传播
            if ((*itr)->currentEffect->type == "Fire" && (*itr)->currentEffect->spreadCountdown > 0)
            {
                (*itr)->currentEffect->spreadCountdown -= 1;
                ++itr;
            }
            else
            {
                for (auto effect : (*itr)->effects)
                {
                    effect->setVisible(true);
                }
                effectedItems.push_back(*itr);
                itr = toBeEffectedItems.erase(itr);
            }
        }
        else
        {
            itr = toBeEffectedItems.erase(itr);
        }
    }

    for (auto itr = effectedItems.begin(); itr != effectedItems.end();)
    {
        // 若当前无元素附着，从当前列表中移除该物体
        if ((*itr)->currentEffect == nullptr)
        {
            itr = effectedItems.erase(itr);
            continue;
        }

        // 更新元素效果的存在时长，到时则删去
        if ((*itr)->currentEffect->countdown <= 0)
        {
            if (*itr != nullptr && (*itr)->material->isWood() && dynamic_cast<FireEffect*>((*itr)->currentEffect) !=
                nullptr)
            {
                (*itr)->removeEffect();

                if (dynamic_cast<Platform*>(*itr) != nullptr)
                {
                    for (auto it_p = platforms.begin(); it_p != platforms.end(); ++it_p)
                    {
                        if (*it_p == *itr)
                        {
                            platforms.erase(it_p);
                            break;
                        }
                    }
                }
                else if (dynamic_cast<Weapon*>(*itr) != nullptr)
                {
                    auto weapon = dynamic_cast<Weapon*>(*itr);
                    if (weapon->isMounted() == true)
                    {
                        for (auto character : character)
                        {
                            if (character->getCurrentWeapon() == weapon)
                            {
                                if (character->getBow() == weapon)
                                {
                                    for (auto arrow : character->arrows_)
                                    {
                                        arrow->unequippedFromParent();
                                    }
                                }
                                character->setCurrentWeapon(nullptr);
                            }
                            else if (character->getUnusedWeapon() == weapon)
                            {
                                character->setUnusedWeapon(nullptr);
                            }
                            if (character->getMeleeWeapon() == weapon)
                            {
                                character->setMeleeWeapon(nullptr);
                            }
                            else if (character->getBow() == weapon)
                            {
                                character->setBow(nullptr);
                            }
                        }
                    }
                    else
                    {
                        for (auto it_w = spareWeapons.begin(); it_w != spareWeapons.end(); ++it_w)
                        {
                            if (*it_w == weapon)
                            {
                                spareWeapons.erase(it_w);
                                break;
                            }
                        }
                    }
                }
                delete (*itr);
                *itr = nullptr;
            }
            else
            {
                (*itr)->removeEffect();
            }
            itr = effectedItems.erase(itr);
        }
        else
        {
            if (dynamic_cast<Character*>((*itr)) != nullptr)
            {
                auto character = dynamic_cast<Character*>(*itr);
                if (character->currentEffect->type != character->getArmorSuit()->proofType)
                {
                    character->setHitPoints(character->getHitPoints() - character->currentEffect->damagePerFrame);

                    // 元素效果传播到角色手中的武器上
                    spreadEffect(character->currentEffect, character->getCurrentWeapon());
                    spreadEffect(character->currentEffect, character->getUnusedWeapon());

                    // 若角色与平台有接触，传播元素效果
                    for (auto platform : platforms)
                    {
                        if (character->getTopHeight() <= platform->getBottomBorder() && character->getBottomHeight() >=
                            platform->getTopBorder() &&
                            character->x() >= platform->getLeftBorder() && character->x() <= platform->getRightBorder())
                        {
                            spreadEffect(character->currentEffect, platform);
                        }
                    }

                    // 若角色与闲置武器有接触，传播元素效果
                    for (auto weapon : spareWeapons)
                    {
                        if (weapon->isOnAttack() == false && weapon->isMounted() == false)
                        {
                            if (QLineF(character->pos(), weapon->pos()).length() <= 50)
                            {
                                spreadEffect(character->currentEffect, weapon);
                            }
                        }
                    }
                }
            }
            else if (dynamic_cast<Platform*>((*itr)) != nullptr)
            {
                auto platform = dynamic_cast<Platform*>(*itr);
                // 若平台与角色有接触，传播元素效果
                for (auto character : character)
                {
                    if (character->getTopHeight() <= platform->getBottomBorder() && character->getBottomHeight() >=
                        platform->getTopBorder() &&
                        character->x() >= platform->getLeftBorder() && character->x() <= platform->getRightBorder())
                    {
                        spreadEffect(platform->currentEffect, character);
                    }
                }

                // 若平台与闲置武器有接触，传播元素效果
                for (auto weapon : spareWeapons)
                {
                    if (weapon->isOnAttack() == false && weapon->isMounted() == false)
                    {
                        if (platform->getTopBorder() == weapon->pos().y() &&
                            platform->getLeftBorder() <= weapon->pos().x() && platform->getRightBorder() >= weapon->
                            pos().x())
                        {
                            spreadEffect(platform->currentEffect, weapon);
                        }
                    }
                }
            }
            else if (dynamic_cast<Weapon*>((*itr)) != nullptr)
            {
                auto weapon = dynamic_cast<Weapon*>(*itr);
                if (weapon->isMounted() == true)
                {
                    for (auto character : character)
                    {
                        if (character->getCurrentWeapon() == weapon || character->getUnusedWeapon() == weapon)
                        {
                            if (weapon->currentEffect->type != character->getArmorSuit()->proofType)
                            {
                                spreadEffect(weapon->currentEffect, character);
                            }
                        }
                    }
                }
                else
                {
                    // 若武器与其他闲置武器有接触，传播元素效果
                    for (auto spareWeapon : spareWeapons)
                    {
                        if (weapon->isOnAttack() == false && weapon->isMounted() == false)
                        {
                            auto pt1 = weapon->pos();
                            auto pt2 = spareWeapon->pos();
                            if (QLineF(pt1, pt2).length() <= 50)
                            {
                                spreadEffect(weapon->currentEffect, spareWeapon);
                            }
                        }
                    }

                    // 若武器与人物有接触，传播元素效果
                    for (auto character : character)
                    {
                        if (weapon->isOnAttack() == false && weapon->isMounted() == false)
                        {
                            if (QLineF(weapon->pos(), character->pos()).length() <= 50)
                            {
                                spreadEffect(weapon->currentEffect, character);
                            }
                        }
                    }
                }
            }
            (*itr)->currentEffect->countdown -= 1;
            ++itr;
        }
    }
}

void BattleScene::processInformation()
{
    infoArea->processInformation(character);
}
