//
// Created by hp on 24-9-2.
//

#include "ArmorSuit.h"

#include "ColdProofArmorSuit.h"
#include "FireProofArmorSuit.h"
#include "LightningProofArmorSuit.h"
#include "OrdinarySuit.h"
#include "../Armors/ColdProofArmor.h"
#include "../Armors/FireProofArmor.h"
#include "../Armors/LightningProofArmor.h"
#include "../Armors/OldShirt.h"
#include "../HeadEquipments/CapOfTheHero.h"
#include "../HeadEquipments/ColdProofHeadEquipment.h"
#include "../HeadEquipments/FireProofHeadEquipment.h"
#include "../HeadEquipments/LightningProofHeadEquipment.h"
#include "../LegEquipments/ColdProofLegEquipment.h"
#include "../LegEquipments/FireProofLegEquipment.h"
#include "../LegEquipments/LightningProofLegEquipment.h"
#include "../LegEquipments/WellWornTrousers.h"

ArmorSuit::ArmorSuit(QGraphicsItem* parent, const QString& pixmapPath): Item(parent, pixmapPath)
{
    setScale(0.8);
    pixmapItem->setPos(-Item::boundingRect().width() / 2, -Item::boundingRect().height() + 10);
    bottomEllipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    // Optionally, set some properties of the ellipse
    bottomEllipseItem->setBrush(Qt::blue); // Fill color
    bottomEllipseItem->setZValue(1);
    topEllipseItem = new QGraphicsEllipseItem(-5, -5 - Item::boundingRect().height(), 10, 10, this);
    topEllipseItem->setBrush(Qt::blue);
    topEllipseItem->setZValue(1);
}

QPointF ArmorSuit::getVelocity() const
{
    return velocity;
}

void ArmorSuit::setVelocity(const QPointF& velocity)
{
    this->velocity = velocity;
}

bool ArmorSuit::isInAir() const
{
    return inAir;
}

void ArmorSuit::setInAir(const bool inAir)
{
    this->inAir = inAir;
}

void ArmorSuit::mountToParent()
{
    Mountable::mountToParent();
    setVisible(false);
}

void ArmorSuit::unmount()
{
    Mountable::unmount();
    delete armor;
    delete legEquipment;
    delete headEquipment;
    armor = nullptr;
    legEquipment = nullptr;
    headEquipment = nullptr;
    setVisible(true);
    setInAir(true);
}

// QString ArmorSuit::getType() const
// {
//     return type;
// }
//
// void ArmorSuit::setType(const QString& type)
// {
//     this->type = type;
// }
