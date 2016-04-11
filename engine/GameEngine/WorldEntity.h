//
//  WorldEntity.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef WORLDENTITY_H
#define WORLDENTITY_H

#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"

class WorldEntity : public GameObject
{
public:
    Transform Transform;
    BoundingSphere Bounds;
    
    bool OnInitialize() override;
};


#endif /* WorldEntity_hpp */