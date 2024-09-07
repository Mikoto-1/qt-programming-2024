//
// Created by gerw on 8/21/24.
//

#include "Mountable.h"

void Mountable::unmount()
{
    mounted = false;
}

bool Mountable::isMounted() const
{
    return mounted;
}

bool Mountable::isMountable() const
{
    return mountable;
}

void Mountable::setMountable(const bool mountable)
{
    this->mountable = mountable;
}

void Mountable::mountToParent()
{
    mounted = true;
}
