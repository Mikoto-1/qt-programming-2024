//
// Created by hp on 24-9-5.
//

#ifndef EFFECT_H
#define EFFECT_H
#include "../Item.h"


class Effect : public Item
{
public:
    explicit Effect(QGraphicsItem* parent, const QString& pixmapPath);

    int countdown;

    int spreadCountdown{};

    int initialCountdown;

    qreal damagePerFrame = 0;

    QString type = "";
};



#endif //EFFECT_H
