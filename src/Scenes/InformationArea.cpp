//
// Created by hp on 24-9-3.
//

#include "InformationArea.h"

#include <qbrush.h>

#include "../Items/ArmorSuits/ColdProofArmorSuit.h"
#include "../Items/ArmorSuits/FireProofArmorSuit.h"
#include "../Items/ArmorSuits/LightningProofArmorSuit.h"
#include "../Items/ArmorSuits/OrdinarySuit.h"
#include "../Items/Bows/EpicMetalBow.h"
#include "../Items/Bows/EpicWoodBow.h"
#include "../Items/Bows/LegendaryMetalBow.h"
#include "../Items/Bows/LegendaryWoodBow.h"
#include "../Items/Bows/OrdinaryMetalBow.h"
#include "../Items/Bows/OrdinaryWoodBow.h"
#include "../Items/Characters/Character.h"
#include "../Items/Effects/FireEffect.h"
#include "../Items/Effects/IceEffect.h"
#include "../Items/Effects/LightningEffect.h"
#include "../Items/LargeSwords/FireLargeSword.h"
#include "../Items/LargeSwords/IceLargeSword.h"
#include "../Items/LargeSwords/LargeSword.h"
#include "../Items/LargeSwords/LightningLargeSword.h"
#include "../Items/LargeSwords/MetalLargeSword.h"
#include "../Items/LargeSwords/WoodLargeSword.h"
#include "../Items/Spears/FireSpear.h"
#include "../Items/Spears/IceSpear.h"
#include "../Items/Spears/LightningSpear.h"
#include "../Items/Spears/MetalSpear.h"
#include "../Items/Spears/Spear.h"
#include "../Items/Spears/WoodSpear.h"
#include "../Items/Swords/FireSword.h"
#include "../Items/Swords/IceSword.h"
#include "../Items/Swords/LightningSword.h"
#include "../Items/Swords/MetalSword.h"
#include "../Items/Swords/Sword.h"
#include "../Items/Swords/WoodSword.h"

InformationArea::InformationArea(int x, int y, int w, int h, QGraphicsItem* parent) : QGraphicsRectItem(x, y, w, h, parent)
{
    setPos(0,640);
    setZValue(1);
    setOpacity(0.6);
    setBrush(QBrush(Qt::black));

    hitPointBar[0] = new QGraphicsRectItem(0,0,200,20,this);
    hitPointBar[0]->setBrush(Qt::green);
    hitPointBar[0]->setOpacity(1);
    hitPointBar[0]->setParentItem(this);
    hitPointBar[1] = new QGraphicsRectItem(740,0,200,20,this);
    hitPointBar[1]->setBrush(Qt::green);
    hitPointBar[1]->setOpacity(1);
    hitPointBar[1]->setParentItem(this);

    hitPointHint[0] = new QGraphicsTextItem(this);
    hitPointHint[0]->setFont(QFont("Arial", 12, QFont::Bold));
    hitPointHint[0]->setPos(200,0);
    hitPointHint[0]->setOpacity(1);
    hitPointHint[0]->setPlainText("100");
    hitPointHint[0]->setDefaultTextColor(Qt::green);
    hitPointHint[1] = new QGraphicsTextItem(this);
    hitPointHint[1]->setFont(QFont("Arial", 12, QFont::Bold));
    hitPointHint[1]->setPos(940,0);
    hitPointHint[1]->setOpacity(1);
    hitPointHint[1]->setPlainText("100");
    hitPointHint[1]->setDefaultTextColor(Qt::green);

    arrowInformationBox[0] = new ArrowInformationBox(0,0,200,80,this);
    arrowInformationBox[1] = new ArrowInformationBox(0,0,200,80,this);
    arrowInformationBox[0]->setPos(240,0);
    arrowInformationBox[1]->setPos(980,0);

    weaponInformationBox[0] = new WeaponInformationBox(0,0,240,60,this);
    weaponInformationBox[1] = new WeaponInformationBox(0,0,240,60,this);
    weaponInformationBox[0]->setPos(0,20);
    weaponInformationBox[1]->setPos(740,20);

    armorSuitInformationBox[0] = new ArmorSuitInformationBox(0,0,100,60,this);
    armorSuitInformationBox[0]->setPos(440,0);
    armorSuitInformationBox[1] = new ArmorSuitInformationBox(0,0,100,60,this);
    armorSuitInformationBox[1]->setPos(1180,0);

    deBuffInformationBox[0] = new DeBuffInformationBox(0,0,100,20,this);
    deBuffInformationBox[0]->setPos(440,60);
    deBuffInformationBox[1] = new DeBuffInformationBox(0,0,100,20,this);
    deBuffInformationBox[1]->setPos(1180,60);
}

void InformationArea::processInformation(Character* character[2])
{
    // 更新生命值条和数值
    for (int i = 0; i < 2; i++)
    {
        auto hitPointsRate = character[i]->getHitPoints() / character[i]->maxHitPoints;
        hitPointBar[i]->setRect(740 * i,0,200 * hitPointsRate,20);
        hitPointHint[i]->setPlainText(QString::number(character[i]->getHitPoints()));
        if (hitPointsRate <= 0.6)
        {
            hitPointBar[i]->setBrush(Qt::yellow);
            hitPointHint[i]->setDefaultTextColor(Qt::yellow);
        }
        if (hitPointsRate <= 0.3)
        {
            hitPointBar[i]->setBrush(Qt::red);
            hitPointHint[i]->setDefaultTextColor(Qt::red);
        }
    }

    // 更新箭的剩余数量和当前使用的箭
    for (int i = 0; i < 2; i++)
    {
        for (const auto& type : character[i]->arrowNumbers.keys())
        {
            auto newNumber = QString::number(character[i]->arrowNumbers[type]);
            int index = 0;
            if (type == "Ordinary")
            {
                index = 0;
            }
            else if (type == "Fire")
            {
                index = 1;
            }
            else if (type == "Ice")
            {
                index = 2;
            }
            else if (type == "Lightning")
            {
                index = 3;
            }
            arrowInformationBox[i]->arrowNumbers[index]->setPlainText(newNumber);

            arrowInformationBox[i]->topIndicator->setVisible(false);
            arrowInformationBox[i]->bottomIndicator->setVisible(false);
            if (character[i]->getCurrentArrow() != nullptr)
            {
                int index1 = 0;
                auto type1 = character[i]->getCurrentArrow()->getType();
                if (type1 == "Ordinary")
                {
                    index1 = 0;
                }
                else if (type1 == "Fire")
                {
                    index1 = 1;
                }
                else if (type1 == "Ice")
                {
                    index1 = 2;
                }
                else if (type1 == "Lightning")
                {
                    index1 = 3;
                }
                arrowInformationBox[i]->topIndicator->setVisible(true);
                arrowInformationBox[i]->bottomIndicator->setVisible(true);
                arrowInformationBox[i]->topIndicator->setPos(50*index1 + 25, 0);
                arrowInformationBox[i]->bottomIndicator->setPos(50*index1 + 25, 80);
            }
        }
    }

    // 更新持有的武器和当前使用的武器
    for (int i = 0; i < 2; i++)
    {
        weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap());
        weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap());
        weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("");
        weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("");
        weaponInformationBox[i]->bowMaterialText->setPlainText("");
        weaponInformationBox[i]->bowTypeText->setPlainText("");
        if (auto melee = character[i]->getMeleeWeapon(); melee != nullptr)
        {
            if (dynamic_cast<Sword*>(melee))
            {
                if (dynamic_cast<FireSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Swords/FireSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("火双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::red);
                }
                else if (dynamic_cast<IceSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Swords/IceSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("冰双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::blue);
                }
                else if (dynamic_cast<LightningSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Swords/LightningSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("电双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::magenta);
                }
                else if (dynamic_cast<WoodSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Swords/WoodSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("木制");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkRed);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("木双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::black);
                }
                else if (dynamic_cast<MetalSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Swords/MetalSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkRed);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::black);
                }
            }
            else if (dynamic_cast<LargeSword*>(melee))
            {
                if (dynamic_cast<FireLargeSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/LargeSwords/FireLargeSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("火双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::red);
                }
                else if (dynamic_cast<IceLargeSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/LargeSwords/IceLargeSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("冰双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::blue);
                }
                else if (dynamic_cast<LightningLargeSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/LargeSwords/LightningLargeSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("电双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::magenta);
                }
                else if (dynamic_cast<WoodLargeSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/LargeSwords/WoodLargeSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("木制");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkRed);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("木双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::black);
                }
                else if (dynamic_cast<MetalLargeSword*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/LargeSwords/MetalLargeSword.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("双手剑");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::black);
                }
            }
            else if(dynamic_cast<Spear*>(melee))
            {
                if (dynamic_cast<FireSpear*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Spears/FireSpear.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("火长矛");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::red);
                }
                else if (dynamic_cast<IceSpear*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Spears/IceSpear.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("冰长矛");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::blue);
                }
                else if (dynamic_cast<LightningSpear*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Spears/LightningSpear.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("电长矛");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::magenta);
                }
                else if (dynamic_cast<WoodSpear*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Spears/WoodSpear.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("木制");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkRed);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("木长矛");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::black);
                }
                else if (dynamic_cast<MetalSpear*>(melee))
                {
                    weaponInformationBox[i]->meleeWeaponPixItem->setPixmap(QPixmap(":/Items/Spears/MetalSpear.png"));
                    weaponInformationBox[i]->meleeWeaponMaterialText->setPlainText("金属");
                    weaponInformationBox[i]->meleeWeaponMaterialText->setDefaultTextColor(Qt::darkGray);
                    weaponInformationBox[i]->meleeWeaponTypeText->setPlainText("长矛");
                    weaponInformationBox[i]->meleeWeaponTypeText->setDefaultTextColor(Qt::black);
                }
            }
        }
        if (auto bow = character[i]->getBow(); bow != nullptr)
        {
            if (dynamic_cast<OrdinaryWoodBow*>(bow))
            {
                weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap(":/Items/Bows/OrdinaryWoodBow.png"));
                weaponInformationBox[i]->bowMaterialText->setPlainText("木制");
                weaponInformationBox[i]->bowMaterialText->setDefaultTextColor(Qt::darkRed);
                weaponInformationBox[i]->bowTypeText->setPlainText("★");
                weaponInformationBox[i]->bowTypeText->setDefaultTextColor(Qt::yellow);
            }
            else if (dynamic_cast<OrdinaryMetalBow*>(bow))
            {
                weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap(":/Items/Bows/OrdinaryMetalBow.png"));
                weaponInformationBox[i]->bowMaterialText->setPlainText("金属");
                weaponInformationBox[i]->bowMaterialText->setDefaultTextColor(Qt::darkGray);
                weaponInformationBox[i]->bowTypeText->setPlainText("★");
                weaponInformationBox[i]->bowTypeText->setDefaultTextColor(Qt::yellow);
            }
            else if (dynamic_cast<LegendaryWoodBow*>(bow))
            {
                weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap(":/Items/Bows/LegendaryWoodBow.png"));
                weaponInformationBox[i]->bowMaterialText->setPlainText("木制");
                weaponInformationBox[i]->bowMaterialText->setDefaultTextColor(Qt::darkRed);
                weaponInformationBox[i]->bowTypeText->setPlainText("★★");
                weaponInformationBox[i]->bowTypeText->setDefaultTextColor(Qt::yellow);
            }
            else if (dynamic_cast<LegendaryMetalBow*>(bow))
            {
                weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap(":/Items/Bows/LegendaryMetalBow.png"));
                weaponInformationBox[i]->bowMaterialText->setPlainText("金属");
                weaponInformationBox[i]->bowMaterialText->setDefaultTextColor(Qt::darkGray);
                weaponInformationBox[i]->bowTypeText->setPlainText("★★");
                weaponInformationBox[i]->bowTypeText->setDefaultTextColor(Qt::yellow);
            }
            else if (dynamic_cast<EpicWoodBow*>(bow))
            {
                weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap(":/Items/Bows/EpicWoodBow.png"));
                weaponInformationBox[i]->bowMaterialText->setPlainText("木制");
                weaponInformationBox[i]->bowMaterialText->setDefaultTextColor(Qt::darkRed);
                weaponInformationBox[i]->bowTypeText->setPlainText("★★★");
                weaponInformationBox[i]->bowTypeText->setDefaultTextColor(Qt::yellow);
            }
            else if (dynamic_cast<EpicMetalBow*>(bow))
            {
                weaponInformationBox[i]->bowPixItem->setPixmap(QPixmap(":/Items/Bows/EpicMetalBow.png"));
                weaponInformationBox[i]->bowMaterialText->setPlainText("金属");
                weaponInformationBox[i]->bowMaterialText->setDefaultTextColor(Qt::darkGray);
                weaponInformationBox[i]->bowTypeText->setPlainText("★★★");
                weaponInformationBox[i]->bowTypeText->setDefaultTextColor(Qt::yellow);
            }
        }
        if (auto currentWeapon = character[i]->getCurrentWeapon(); currentWeapon != nullptr)
        {
            if (currentWeapon == character[i]->getMeleeWeapon())
            {
                weaponInformationBox[i]->meleeWeaponBox->setBrush(Qt::cyan);
                weaponInformationBox[i]->bowBox->setBrush(Qt::white);
            }
            else if (currentWeapon == character[i]->getBow())
            {
                weaponInformationBox[i]->bowBox->setBrush(Qt::cyan);
                weaponInformationBox[i]->meleeWeaponBox->setBrush(Qt::white);
            }
        }
        else
        {
            weaponInformationBox[i]->meleeWeaponBox->setBrush(Qt::white);
            weaponInformationBox[i]->bowBox->setBrush(Qt::white);
        }
    }

    // 更新当前使用的盔甲
    for (int i = 0; i < 2; i++)
    {
        auto armorSuit = character[i]->getArmorSuit();
        if (armorSuit != nullptr)
        {
            if (dynamic_cast<OrdinarySuit*>(armorSuit) != nullptr)
            {
                armorSuitInformationBox[i]->armorSuitPixmapItem->setPixmap(QPixmap(":/Items/Armors/OldShirt/BotW_Old_Shirt_Icon.png"));
                armorSuitInformationBox[i]->armorSuitTextItem->setPlainText("无免疫");
                armorSuitInformationBox[i]->armorSuitTextItem->setDefaultTextColor(Qt::black);
            }
            else if (dynamic_cast<FireProofArmorSuit*>(armorSuit) != nullptr)
            {
                armorSuitInformationBox[i]->armorSuitPixmapItem->setPixmap(QPixmap(":/Items/Armors/FireProofArmor.png"));
                armorSuitInformationBox[i]->armorSuitTextItem->setPlainText("免疫火");
                armorSuitInformationBox[i]->armorSuitTextItem->setDefaultTextColor(Qt::red);
            }
            else if (dynamic_cast<ColdProofArmorSuit*>(armorSuit) != nullptr)
            {
                armorSuitInformationBox[i]->armorSuitPixmapItem->setPixmap(QPixmap(":/Items/Armors/ColdProofArmor.png"));
                armorSuitInformationBox[i]->armorSuitTextItem->setPlainText("免疫冰");
                armorSuitInformationBox[i]->armorSuitTextItem->setDefaultTextColor(Qt::blue);
            }
            else if (dynamic_cast<LightningProofArmorSuit*>(armorSuit) != nullptr)
            {
                armorSuitInformationBox[i]->armorSuitPixmapItem->setPixmap(QPixmap(":/Items/Armors/LightningProofArmor.png"));
                armorSuitInformationBox[i]->armorSuitTextItem->setPlainText("免疫电");
                armorSuitInformationBox[i]->armorSuitTextItem->setDefaultTextColor(Qt::magenta);
            }
        }
    }

    // 更新当前的元素附着状态
    for (int i = 0; i < 2; i++)
    {
        auto element = character[i]->currentEffect;
        deBuffInformationBox[i]->deBuffHint->setPlainText("");
        if (element != nullptr)
        {
            if (dynamic_cast<FireEffect*>(element) != nullptr)
            {
                deBuffInformationBox[i]->deBuffHint->setPlainText("DeBuff: 🔥");
                deBuffInformationBox[i]->deBuffHint->setDefaultTextColor(Qt::red);
                deBuffInformationBox[i]->deBuffHint->setY(-4);
            }
            else if (dynamic_cast<IceEffect*>(element) != nullptr)
            {
                deBuffInformationBox[i]->deBuffHint->setPlainText("DeBuff: ❄");
                deBuffInformationBox[i]->deBuffHint->setDefaultTextColor(Qt::blue);
                deBuffInformationBox[i]->deBuffHint->setY(0);
            }
            else if (dynamic_cast<LightningEffect*>(element) != nullptr)
            {
                deBuffInformationBox[i]->deBuffHint->setPlainText("DeBuff: ⚡");
                deBuffInformationBox[i]->deBuffHint->setDefaultTextColor(Qt::magenta);
                deBuffInformationBox[i]->deBuffHint->setY(-4);
            }
        }
    }
}
