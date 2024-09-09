//
// Created by gerw on 8/20/24.
//

#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include <QApplication>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include "InformationArea.h"
#include "Scene.h"
#include "../Items/ArmorSuits/ArmorSuit.h"
#include "../Items/Characters/AIPlayer.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Effects/Effect.h"
#include "../Items/Platforms/Platform.h"

class BattleScene : public Scene
{
    Q_OBJECT

public:
    explicit BattleScene(QObject* parent, const QString& gameMode);

    void processInput() override;

    void processAIActions();

    void processAIMoving(AIPlayer* aiPlayer);

    void processAIApproach(AIPlayer* aiPlayer);

    void processMovement() override;

    void processPicking() override;

    void processLanding();

    void processCollision();

    void processCheatCode(const QString& cheatCode);

    void processAttacking();

    void processAnimationAfterHit();

    void processHitting();

    void addEffect(Weapon* weapon, Item* item);

    void spreadEffect(Effect* effect, Item* item);

    void processEffect();

    void processInformation();

signals:
    void gameOver(QString); // signal to be emitted when the game is over

protected slots:
    void update() override;

    void gameOverUpdate();

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

private:
    Mountable* findNearestUnmountedMountable(const QPointF& pos,
                                             qreal distance_threshold = std::numeric_limits<qreal>::max());

    Mountable* pickupMountable(Character* character, Mountable* mountable);

    void discardWeapon(Character* character);

    void shootArrow(Character* character);

    void autoGenerateItems();

    bool eventFilter(QObject* watched, QEvent* event) override;

    void endTheGame();

    Map* map;
    Character* character[2] = {};
    QPointF gravitationalAcceleration = QPointF(0,0.003);
    QVector<Platform*> platforms;

public:
    [[nodiscard]] QVector<Platform*> get_platforms() const;

private:
    QString gameMode;

public:
    [[nodiscard]] QString get_game_mode() const;

private:
    QVector<Weapon*> spareWeapons;
    QVector<ArmorSuit*> spareArmorSuits;
    QVector<Effect*> effects;
    QVector<Item*> effectedItems;
    QVector<Item*> toBeEffectedItems;
    QGraphicsProxyWidget *cheatCodeLineEditProxy;
    QLineEdit* cheatCodeInputLineEdit;
    InformationArea* infoArea;
    bool isGameOver = false;
    int gameOverCountdown = 90;
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
