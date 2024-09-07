//
// Created by hp on 24-9-2.
//

#ifndef LIGHTNINGPROOFARMORSUIT_H
#define LIGHTNINGPROOFARMORSUIT_H
#include <QGraphicsItem>

#include "ArmorSuit.h"


class LightningProofArmorSuit : public ArmorSuit
{
public:
    explicit LightningProofArmorSuit(QGraphicsItem* parent = nullptr);

    void mountToParent() override;
};



#endif //LIGHTNINGPROOFARMORSUIT_H
