//
// Created by hp on 24-9-2.
//

#ifndef ARMORSUIT_H
#define ARMORSUIT_H
#include "../Item.h"
#include "../Mountable.h"
#include "../HeadEquipments/HeadEquipment.h"
#include "../LegEquipments/LegEquipment.h"


class Armor;

class ArmorSuit : public Item, public Mountable
{
public:
    explicit ArmorSuit(QGraphicsItem* parent, const QString& pixmapPath);

    [[nodiscard]] QPointF getVelocity() const;

    void setVelocity(const QPointF& velocity);

    [[nodiscard]] bool isInAir() const;

    void setInAir(bool inAir);

    const double scale = 0.8;

    void mountToParent() override;

    void unmount() override;

    Armor* armor{nullptr};

    LegEquipment* legEquipment{nullptr};

    HeadEquipment* headEquipment{nullptr};

    QString proofType{""};

private:

    bool inAir{true};

    QPointF velocity{};

    QGraphicsEllipseItem* bottomEllipseItem;    // For debugging.

    QGraphicsEllipseItem* topEllipseItem;       // For debugging.
};



#endif //ARMORSUIT_H
