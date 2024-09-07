//
// Created by hp on 24-9-2.
//

#include "ColdProofArmorSuit.h"

#include "../Armors/ColdProofArmor.h"
#include "../HeadEquipments/ColdProofHeadEquipment.h"
#include "../LegEquipments/ColdProofLegEquipment.h"

ColdProofArmorSuit::ColdProofArmorSuit(QGraphicsItem* parent) : ArmorSuit(parent, ":/Items/Armors/ColdProofArmor.png")
{
    proofType = "Ice";
}

void ColdProofArmorSuit::mountToParent()
{
    ArmorSuit::mountToParent();
    const auto armor = new ColdProofArmor(parentItem());
    const auto legEquipment = new ColdProofLegEquipment(parentItem());
    const auto headEquipment = new ColdProofHeadEquipment(parentItem());
    armor->mountToParent();
    legEquipment->mountToParent();
    headEquipment->mountToParent();
    this->armor = armor;
    this->legEquipment = legEquipment;
    this->headEquipment = headEquipment;
}
