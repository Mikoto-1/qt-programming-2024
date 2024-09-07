//
// Created by hp on 24-9-3.
//

#include "ArrowInformationBox.h"

#include <qbrush.h>
#include <qfont.h>

ArrowInformationBox::ArrowInformationBox(int x, int y, int w, int h, QGraphicsItem* parent) : QGraphicsRectItem(x, y, w, h, parent)
{
    setZValue(1);
    setOpacity(1);
    setBrush(QBrush(Qt::white));

    arrows[0] = new QGraphicsPixmapItem(QPixmap(":/Items/Arrows/Arrow.png"), this);
    arrows[1] = new QGraphicsPixmapItem(QPixmap(":/Items/Arrows/FireArrow.png"), this);
    arrows[2] = new QGraphicsPixmapItem(QPixmap(":/Items/Arrows/IceArrow.png"), this);
    arrows[3] = new QGraphicsPixmapItem(QPixmap(":/Items/Arrows/LightningArrow.png"), this);

    for (int i = 0; i < 4; i++)
    {
        arrows[i]->setScale(0.6);
        arrows[i]->setPos(50 * i, 20);
        arrows[i]->setOpacity(1);
    }

    for (int i = 0; i < 4; i++)
    {
        arrowTypes[i] = new QGraphicsTextItem(this);
        arrowTypes[i]->setFont(QFont("Arial", 12, QFont::Bold));
        arrowTypes[i]->setPos(50 * i, 0);
        arrowTypes[i]->setOpacity(1);
        arrowTypes[i]->setZValue(1);
        arrowTypes[i]->setPlainText(arrowNames[i]);

        arrowNumbers[i] = new QGraphicsTextItem(this);
        arrowNumbers[i]->setFont(QFont("Arial", 12, QFont::Bold));
        arrowNumbers[i]->setPos(50 * i, 60);
        arrowNumbers[i]->setOpacity(1);
        arrowNumbers[i]->setZValue(1);
        arrowNumbers[i]->setPlainText(QString::number(0));

        if (arrowNames[i] == "无")
        {
            arrowTypes[i]->setDefaultTextColor(Qt::black);
            arrowNumbers[i]->setDefaultTextColor(Qt::black);
        }
        else if (arrowNames[i] == "火")
        {
            arrowTypes[i]->setDefaultTextColor(Qt::red);
            arrowNumbers[i]->setDefaultTextColor(Qt::red);
        }
        else if (arrowNames[i] == "冰")
        {
            arrowTypes[i]->setDefaultTextColor(Qt::blue);
            arrowNumbers[i]->setDefaultTextColor(Qt::blue);
        }
        else if (arrowNames[i] == "电")
        {
            arrowTypes[i]->setDefaultTextColor(Qt::magenta);
            arrowNumbers[i]->setDefaultTextColor(Qt::magenta);
        }
    }

    QPolygonF topTriangle;
    topTriangle << QPointF(0, 0) << QPointF(12,0) << QPointF(6,12);
    QPolygonF bottomTriangle;
    bottomTriangle << QPointF(0,0) << QPointF(12,0) << QPointF(6,-12);

    topIndicator = new QGraphicsPolygonItem(topTriangle,this);
    bottomIndicator = new QGraphicsPolygonItem(bottomTriangle,this);

    topIndicator->setBrush(QBrush(Qt::cyan));
    bottomIndicator->setBrush(QBrush(Qt::cyan));

    topIndicator->setZValue(2);
    bottomIndicator->setZValue(2);

    topIndicator->setOpacity(1);
    bottomIndicator->setOpacity(1);

    topIndicator->setPos(25,0);
    bottomIndicator->setPos(25,0);

    topIndicator->setVisible(false);
    bottomIndicator->setVisible(false);
}
