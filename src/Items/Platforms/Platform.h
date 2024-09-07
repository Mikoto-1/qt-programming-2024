//
// Created by hp on 24-8-30.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../Item.h"

class Platform : public Item
{
public:
    explicit Platform(QGraphicsItem* parent, const QString& pixmapPath);
    [[nodiscard]] qreal getHeight() const;
    [[nodiscard]] qreal getWidth() const;
    [[nodiscard]] qreal getLeftBorder() const;
    [[nodiscard]] qreal getRightBorder() const;
    [[nodiscard]] qreal getTopBorder() const;
    [[nodiscard]] qreal getBottomBorder() const;

private:
    const int scale = 5;
    QGraphicsEllipseItem* topEllipseItem;
    QGraphicsEllipseItem* bottomEllipseItem;
    QGraphicsEllipseItem* leftEllipseItem;
    QGraphicsEllipseItem* rightEllipseItem;
};


#endif //PLATFORM_H
