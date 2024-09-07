//
// Created by hp on 24-9-2.
//

#ifndef FIREPROOFARMORSUIT_H
#define FIREPROOFARMORSUIT_H
#include "ArmorSuit.h"


class FireProofArmorSuit : public ArmorSuit
{
public:
    explicit FireProofArmorSuit(QGraphicsItem* parent = nullptr);

    void mountToParent() override;
};



#endif //FIREPROOFARMORSUIT_H
