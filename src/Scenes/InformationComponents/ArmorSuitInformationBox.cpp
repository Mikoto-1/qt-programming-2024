//
// Created by hp on 24-9-4.
//

#include "ArmorSuitInformationBox.h"

#include <qbrush.h>
#include <qfont.h>

ArmorSuitInformationBox::ArmorSuitInformationBox(int x, int y, int w, int h, QGraphicsItem* parent) : QGraphicsRectItem(x, y, w, h, parent)
{
    setBrush(QBrush(Qt::white));

    armorSuitPixmapItem = new QGraphicsPixmapItem(this);
    armorSuitPixmapItem->setPixmap(QPixmap(":/Items/Armors/OldShirt/BotW_Old_Shirt_Icon.png"));
    armorSuitPixmapItem->setScale(0.45);
    armorSuitPixmapItem->setPos(0, 0);

    armorSuitTextItem = new QGraphicsTextItem(this);
    armorSuitTextItem->setPos(72,0);
    armorSuitTextItem->setZValue(1);
    armorSuitTextItem->setFont(QFont("Arial", 10, QFont::Bold));

    armorSuitTextItem->setPlainText("无免疫");
    armorSuitTextItem->setDefaultTextColor("black");
    armorSuitTextItem->setTextWidth(15);
}
