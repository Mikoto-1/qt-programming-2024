//
// Created by hp on 24-9-2.
//

#ifndef LIGHTNINGARROW_H
#define LIGHTNINGARROW_H
#include "Arrow.h"
#include "../../DamageType/LightningDamage.h"


class LightningArrow : public Arrow
{
public:
    explicit LightningArrow(QGraphicsItem* parent = nullptr);

    QString getType() override;
};



#endif //LIGHTNINGARROW_H
