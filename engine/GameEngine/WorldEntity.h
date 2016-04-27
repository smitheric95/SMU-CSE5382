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
    BoundingSphere getTransformedBounds(){
        Vector4 c = Bounds.boundCenter;
        Vector4 o = Bounds.boundCenter + Vector4(Bounds.boundRadius, 0, 0, 0);
        
        Vector3 cPrime = Transform.GetMatrix() * c;
        Vector3 oPrime = Transform.GetMatrix() * o;
        float rPrime = oPrime.distance(cPrime);
        
        return BoundingSphere(cPrime, rPrime);
    }
    
    void OnPreUpdate(const GameTime& time) override;
    
};


#endif /* WorldEntity_hpp */