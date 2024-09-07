//
// Created by hp on 24-9-4.
//

#ifndef WEAPONINFORMATIONBOX_H
#define WEAPONINFORMATIONBOX_H
#include <QGraphicsItem>


class WeaponInformationBox : public QGraphicsRectItem
{
public:
    WeaponInformationBox(int x, int y, int w, int h, QGraphicsItem* parent = nullptr);

    QGraphicsRectItem* meleeWeaponBox;

    QGraphicsRectItem* bowBox;

    QGraphicsPixmapItem* meleeWeaponPixItem = nullptr;

    QGraphicsPixmapItem* bowPixItem = nullptr;

    QGraphicsTextItem* meleeWeaponMaterialText = nullptr;

    QGraphicsTextItem* bowMaterialText = nullptr;

    QGraphicsTextItem* meleeWeaponTypeText = nullptr;

    QGraphicsTextItem* bowTypeText = nullptr;
};



#endif //WEAPONINFORMATIONBOX_H
