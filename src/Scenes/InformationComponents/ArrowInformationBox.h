//
// Created by hp on 24-9-3.
//

#ifndef ARROWINFORMATIONBOX_H
#define ARROWINFORMATIONBOX_H
#include <QGraphicsItem>


class ArrowInformationBox : public QGraphicsRectItem
{
public:
    ArrowInformationBox(int x, int y, int w, int h, QGraphicsItem* parent = nullptr);

    QGraphicsPixmapItem* arrows[4] = {};

    QGraphicsTextItem* arrowTypes[4] = {};

    QGraphicsTextItem* arrowNumbers[4] = {};

    const QList<QString> arrowNames = {"无","火","冰","电"};

    QGraphicsPolygonItem* topIndicator = nullptr;

    QGraphicsPolygonItem* bottomIndicator = nullptr;
};



#endif //ARROWINFORMATIONBOX_H
