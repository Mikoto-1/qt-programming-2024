//
// Created by hp on 24-9-5.
//

#ifndef DEBUFFINFORMATIONBOX_H
#define DEBUFFINFORMATIONBOX_H
#include "../../Items/Item.h"


class DeBuffInformationBox : public QGraphicsRectItem
{
public:
    DeBuffInformationBox(int x, int y, int w, int h, QGraphicsItem* parent = nullptr);

    QGraphicsTextItem* deBuffHint;
};



#endif //DEBUFFINFORMATIONBOX_H
