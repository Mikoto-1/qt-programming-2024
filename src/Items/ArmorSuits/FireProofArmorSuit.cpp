//
// Created by hp on 24-9-2.
//

#include "FireProofArmorSuit.h"

#include "../Armors/FireProofArmor.h"
#include "../HeadEquipments/FireProofHeadEquipment.h"
#include "../LegEquipments/FireProofLegEquipment.h"

FireProofArmorSuit::FireProofArmorSuit(QGraphicsItem* parent) : ArmorSuit(parent, ":/Items/Armors/FireProofArmor.png")
{
    proofType = "Fire";
}

void FireProofArmorSuit::mountToParent()
{
    ArmorSuit::mountToParent();
    const auto armor = new FireProofArmor(parentItem());
    const auto legEquipment = new FireProofLegEquipment(parentItem());
    const auto headEquipment = new FireProofHeadEquipment(parentItem());
    armor->mountToParent();
    legEquipment->mountToParent();
    headEquipment->mountToParent();
    this->armor = armor;
    this->legEquipment = legEquipment;
    this->headEquipment = headEquipment;
}
