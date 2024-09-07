//
// Created by hp on 24-9-4.
//

#include "WeaponInformationBox.h"

#include <qbrush.h>
#include <qfont.h>

WeaponInformationBox::WeaponInformationBox(int x, int y, int w, int h, QGraphicsItem* parent) : QGraphicsRectItem(
    x, y, w, h, parent)
{
    setZValue(1);
    setOpacity(1);
    setBrush(QBrush(Qt::white));

    meleeWeaponBox = new QGraphicsRectItem(0, 0, 120, 60, this);
    bowBox = new QGraphicsRectItem(0, 0, 120, 60, this);
    bowBox->setPos(120,0);

    meleeWeaponPixItem = new QGraphicsPixmapItem(meleeWeaponBox);
    bowPixItem = new QGraphicsPixmapItem(bowBox);

    meleeWeaponPixItem->setPos(30,0);
    bowPixItem->setPos(30,0);

    meleeWeaponPixItem->setScale(0.6);
    bowPixItem->setScale(0.6);

    meleeWeaponMaterialText = new QGraphicsTextItem(meleeWeaponBox);
    meleeWeaponTypeText = new QGraphicsTextItem(meleeWeaponBox);
    bowMaterialText = new QGraphicsTextItem(bowBox);
    bowTypeText = new QGraphicsTextItem(bowBox);

    meleeWeaponMaterialText->setPos(0,0);
    meleeWeaponTypeText->setPos(90,0);
    bowMaterialText->setPos(0,0);
    bowTypeText->setPos(90,0);

    meleeWeaponMaterialText->setFont(QFont("Arial", 8, QFont::Bold));;
    meleeWeaponTypeText->setFont(QFont("Arial", 8, QFont::Bold));
    bowMaterialText->setFont(QFont("Arial", 8, QFont::Bold));
    bowTypeText->setFont(QFont("Arial", 8, QFont::Bold));

    meleeWeaponMaterialText->setTextWidth(30);
    meleeWeaponTypeText->setTextWidth(30);
    bowMaterialText->setTextWidth(30);
    bowTypeText->setTextWidth(30);
}
