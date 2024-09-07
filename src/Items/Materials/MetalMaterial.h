//
// Created by hp on 24-9-4.
//

#ifndef METALMATERIAL_H
#define METALMATERIAL_H
#include "Material.h"


class MetalMaterial : public Material
{
public:
    bool isMetal() override;
};



#endif //METALMATERIAL_H
