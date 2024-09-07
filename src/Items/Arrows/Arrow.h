//
// Created by hp on 24-9-2.
//

#ifndef ARROW_H
#define ARROW_H
#include "../Weapon.h"


class Arrow : public Weapon
{
public:
    explicit Arrow(QGraphicsItem* parent, const QString& pixmapPath);

    void mountToParent() override;

    void unmount() override;

    void equippedToParent() override;

    void unequippedFromParent() override;

    virtual QString getType();
};



#endif //ARROW_H
