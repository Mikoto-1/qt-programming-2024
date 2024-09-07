//
// Created by hp on 24-9-2.
//

#ifndef COLDPROOFARMORSUIT_H
#define COLDPROOFARMORSUIT_H
#include "ArmorSuit.h"


class ColdProofArmorSuit : public ArmorSuit
{
public:
    explicit ColdProofArmorSuit(QGraphicsItem* parent = nullptr);

    void mountToParent() override;
};



#endif //COLDPROOFARMORSUIT_H
