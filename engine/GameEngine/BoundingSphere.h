//
//  BoundingSphere.hpp
//  GameEngine
//
//  Created by Eric Smith on 4/6/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef BoundingSphere_h
#define BoundingSphere_h

#include "Common.h"
#include "Mesh.h"
#include <vector>
#include <cmath>

#include <stdio.h>

class BoundingSphere{
public:
    Vector3 boundCenter;
    float boundRadius;
    
    Vector3 matrix;
    BoundingSphere();
    BoundingSphere(Vector3 center, float radius);
    BoundingSphere(std::vector<Vector3> vertices);
};

#endif /* BoundingSphere_h */
