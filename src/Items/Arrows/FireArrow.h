//
// Created by hp on 24-9-2.
//

#ifndef FIREARROW_H
#define FIREARROW_H
#include "Arrow.h"
#include "../../DamageType/FireDamage.h"


class FireArrow : public Arrow
{
public:
    explicit FireArrow(QGraphicsItem *parent = nullptr);

    QString getType() override;
};



#endif //FIREARROW_H
