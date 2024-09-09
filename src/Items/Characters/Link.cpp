//
// Created by gerw on 8/20/24.
//

#include <memory>
#include "Link.h"
#include "../HeadEquipments/CapOfTheHero.h"
#include "../Armors/OldShirt.h"
#include "../ArmorSuits/FireProofArmorSuit.h"
#include "../ArmorSuits/OrdinarySuit.h"
#include "../Arrows/OrdinaryArrow.h"
#include "../Bows/OrdinaryMetalBow.h"
#include "../Bows/OrdinaryWoodBow.h"
#include "../LargeSwords/WoodLargeSword.h"
#include "../LegEquipments/WellWornTrousers.h"
#include "../Spears/WoodSpear.h"
#include "../Swords/WoodSword.h"

Link::Link(QGraphicsItem* parent) : Character(parent)
{
    armorSuit = new OrdinarySuit(this);
    // meleeWeapon = new WoodSpear(this);
    // bow = new OrdinaryWoodBow(this);
    currentWeapon = meleeWeapon;
    unusedWeapon = bow;
    armorSuit->mountToParent();
    // meleeWeapon->mountToParent();
    // bow->mountToParent();
    // bow->unequippedFromParent();
    armor = armorSuit->armor;
    legEquipment = armorSuit->legEquipment;
    headEquipment = armorSuit->headEquipment;
}
