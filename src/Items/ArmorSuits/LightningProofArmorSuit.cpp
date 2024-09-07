//
// Created by hp on 24-9-2.
//

#include "LightningProofArmorSuit.h"

#include "../Armors/LightningProofArmor.h"
#include "../HeadEquipments/LightningProofHeadEquipment.h"
#include "../LegEquipments/LightningProofLegEquipment.h"

LightningProofArmorSuit::LightningProofArmorSuit(QGraphicsItem* parent) : ArmorSuit(parent, ":/Items/Armors/LightningProofArmor.png")
{
    proofType = "Lightning";
}

void LightningProofArmorSuit::mountToParent()
{
    ArmorSuit::mountToParent();
    const auto armor = new LightningProofArmor(parentItem());
    const auto legEquipment = new LightningProofLegEquipment(parentItem());
    const auto headEquipment = new LightningProofHeadEquipment(parentItem());
    armor->mountToParent();
    legEquipment->mountToParent();
    headEquipment->mountToParent();
    this->armor = armor;
    this->legEquipment = legEquipment;
    this->headEquipment = headEquipment;
}
