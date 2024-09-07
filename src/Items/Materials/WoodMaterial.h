//
// Created by hp on 24-9-4.
//

#ifndef WOODMATERIAL_H
#define WOODMATERIAL_H
#include "Material.h"


class WoodMaterial : public Material
{
public:
    bool isWood() override;
};



#endif //WOODMATERIAL_H
