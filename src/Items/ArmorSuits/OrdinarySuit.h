//
// Created by hp on 24-9-2.
//

#ifndef ORDINARYSUIT_H
#define ORDINARYSUIT_H
#include "ArmorSuit.h"


class OrdinarySuit : public ArmorSuit
{
public:
    explicit OrdinarySuit(QGraphicsItem* parent = nullptr);

    void mountToParent() override;
};



#endif //ORDINARYSUIT_H
