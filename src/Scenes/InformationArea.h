//
// Created by hp on 24-9-3.
//

#ifndef INFORMATIONAREA_H
#define INFORMATIONAREA_H
#include <QGraphicsItem>

#include "InformationComponents/ArmorSuitInformationBox.h"
#include "InformationComponents/ArrowInformationBox.h"
#include "InformationComponents/DeBuffInformationBox.h"
#include "InformationComponents/WeaponInformationBox.h"

class Character;

class InformationArea : public QGraphicsRectItem
{
public:
    explicit InformationArea(int x, int y, int w, int h, QGraphicsItem* parent = nullptr);

    QGraphicsRectItem* hitPointBar[2] = {};

    QGraphicsTextItem* hitPointHint[2] = {};

    ArrowInformationBox* arrowInformationBox[2] = {};

    WeaponInformationBox* weaponInformationBox[2] = {};

    ArmorSuitInformationBox* armorSuitInformationBox[2] = {};

    DeBuffInformationBox* deBuffInformationBox[2] = {};

    void processInformation(Character* character[2]);
};


#endif //INFORMATIONAREA_H
