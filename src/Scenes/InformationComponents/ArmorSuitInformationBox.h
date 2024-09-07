//
// Created by hp on 24-9-4.
//

#ifndef ARMORSUITINFORMATIONBOX_H
#define ARMORSUITINFORMATIONBOX_H
#include <QGraphicsItem>


class ArmorSuitInformationBox : public QGraphicsRectItem
{
public:
    ArmorSuitInformationBox(int x, int y, int w, int h, QGraphicsItem* parent = nullptr);

    QGraphicsPixmapItem* armorSuitPixmapItem = nullptr;

    QGraphicsTextItem* armorSuitTextItem = nullptr;
};



#endif //ARMORSUITINFORMATIONBOX_H
