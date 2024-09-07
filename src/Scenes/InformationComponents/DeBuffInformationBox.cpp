//
// Created by hp on 24-9-5.
//

#include "DebuffInformationBox.h"

DeBuffInformationBox::DeBuffInformationBox(int x, int y, int w, int h, QGraphicsItem* parent) : QGraphicsRectItem(x, y, w, h, parent)
{
    setZValue(1);
    setOpacity(1);
    setBrush(QBrush(Qt::white));

    deBuffHint = new QGraphicsTextItem(this);
    deBuffHint->setFont(QFont("Arial", 12, QFont::Bold));
}
