//
// Created by hp on 24-9-2.
//

#ifndef ICEARROW_H
#define ICEARROW_H
#include "Arrow.h"
#include "../../DamageType/IceDamage.h"


class IceArrow : public Arrow
{
public:
    explicit IceArrow(QGraphicsItem* parent = nullptr);

    QString getType() override;
};



#endif //ICEARROW_H
