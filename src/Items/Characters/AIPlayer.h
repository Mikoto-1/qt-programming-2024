//
// Created by hp on 24-9-7.
//

#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "Link.h"

class BattleScene;

class AIPlayer : public Link
{
public:
    explicit AIPlayer(QGraphicsItem* parent = nullptr);

    QPointF pre_pos = QPointF(0, 0);

    [[nodiscard]] QString getState() const;

    void setIdleState();

    void setApproachingState();

    void setPickTargetState();

    void setAttackState();

    enum state1 {IDLE, MOVING, JUMPING, ATTACKING, HITTING, DEAD};

    QString state = "";

    Item* target = nullptr;
};



#endif //AIPLAYER_H
