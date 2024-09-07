//
// Created by hp on 24-9-4.
//

#ifndef MATERIAL_H
#define MATERIAL_H



class Material {
public:
    virtual ~Material() = default;

    virtual bool isMetal();

    virtual bool isWood();
};



#endif //MATERIAL_H
