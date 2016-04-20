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
        //transform this->bounds by this->transform
        //put em together
        //spit out new sphere
        //this could also occur in transform
        /*
         vec3 c = bonds.Center
         vec3 o = bounds.Center + vec3(bounds.Radius, 0, 0);
         
         c’ = [W] x c  (ship center * ship.transformgetmatrix)
         o’ = [W] x o
         r' = (o' - c').Length();
         
         return BoundingSphere(c', r')
        */
        
        Vector4 c = Bounds.boundCenter;
        Vector4 o = Bounds.boundCenter + Vector3(Bounds.boundRadius, 0, 0);
        
        Vector3 cPrime = Transform.GetMatrix() * c;
        Vector3 oPrime = Transform.GetMatrix() * o;
        float rPrime = oPrime.distance(cPrime);
        
        return BoundingSphere(cPrime, rPrime);
    }
    
    void OnPreUpdate(const GameTime& time) override;
    
};


#endif /* WorldEntity_hpp */