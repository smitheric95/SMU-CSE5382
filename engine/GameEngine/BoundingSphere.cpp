//
//  BoundingSphere.cpp
//  GameEngine
//
//  Created by Eric Smith on 4/6/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "BoundingSphere.h"
#include <limits>
BoundingSphere::BoundingSphere(){
    this->boundCenter = Vector3(0,0,0);
    this->boundRadius = 0.0;
}

BoundingSphere::BoundingSphere(Vector3 center, float radius){
    std::cout << "in boundingsphere " << std::endl;
    
    this->boundRadius = radius;
    this->boundCenter = center;
}
BoundingSphere::BoundingSphere(std::vector<Vector3> vertices){
    //find minX, maxX, repeat for Y and Z
    //use midpoint to find center
    //difference between midpoint and max||min is radius
    
    float maxX, maxY, maxZ;
    maxX = maxY = maxZ = std::numeric_limits<float>::min();
    float minX, minY, minZ;
    minX = minY = minZ = std::numeric_limits<float>::max();
    
    for(int i=0;i<vertices.size();i++){
        if( vertices[i].X > maxX )
            maxX = vertices[i].X;
        else if( vertices[i].X < minX )
            minX = vertices[i].X;
        
        if( vertices[i].Y > maxY )
            maxY = vertices[i].Y;
        else if( vertices[i].Y < minY )
            minY = vertices[i].Y;
        
        if( vertices[i].Z > maxZ )
            maxZ = vertices[i].Z;
        else if( vertices[i].Z < minZ )
            minZ = vertices[i].Z;
    }
    
    float midpointX = (minX + maxX) / 2;
    float midpointY = (minY + maxY) / 2;
    float midpointZ = (minZ + maxZ) / 2;
    
    this->boundCenter = Vector3(midpointX, midpointY, midpointZ);
    
    float diffX = maxX = midpointX;
    float diffY = maxY = midpointY;
    
    if( diffX > diffY )
        this->boundRadius = diffX;
    else
        this->boundRadius = diffY;
    
    
}
//find min and max of each (xyz)
//make something that encapsulates all of those points