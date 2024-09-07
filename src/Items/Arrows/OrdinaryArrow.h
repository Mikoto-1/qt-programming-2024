//
// Created by hp on 24-9-2.
//

#ifndef ORDINARYARROW_H
#define ORDINARYARROW_H
#include "Arrow.h"
#include "../../DamageType/OrdinaryDamage.h"


class OrdinaryArrow : public Arrow
{
public:
    explicit OrdinaryArrow(QGraphicsItem* parent = nullptr);

    QString getType() override;
};



#endif //ORDINARYARROW_H
