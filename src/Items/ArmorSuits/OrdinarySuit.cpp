//
// Created by hp on 24-9-2.
//

#include "OrdinarySuit.h"

#include "../Armors/OldShirt.h"
#include "../HeadEquipments/CapOfTheHero.h"
#include "../LegEquipments/WellWornTrousers.h"

OrdinarySuit::OrdinarySuit(QGraphicsItem* parent) : ArmorSuit(parent, ":/Items/Armors/OldShirt/BotW_Old_Shirt_Icon.png")
{
}

void OrdinarySuit::mountToParent()
{
    ArmorSuit::mountToParent();
    const auto armor = new OldShirt(parentItem());
    const auto legEquipment = new WellWornTrousers(parentItem());
    const auto headEquipment = new CapOfTheHero(parentItem());
    armor->mountToParent();
    legEquipment->mountToParent();
    headEquipment->mountToParent();
    this->armor = armor;
    this->legEquipment = legEquipment;
    this->headEquipment = headEquipment;
}
