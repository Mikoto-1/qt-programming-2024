//
// Created by hp on 24-9-7.
//

#include "AIPlayer.h"

#include "../../Scenes/BattleScene.h"

AIPlayer::AIPlayer(QGraphicsItem* parent) : Link(parent), state("IDLE")
{
}

QString AIPlayer::getState() const
{
    return state;
}

void AIPlayer::setIdleState()
{
    state = "IDLE";
}

void AIPlayer::setApproachingState()
{
    state = "APPROACHING";
}

void AIPlayer::setPickTargetState()
{
    state = "PICK_TARGET";
}

void AIPlayer::setAttackState()
{
    state = "ATTACK";
}
