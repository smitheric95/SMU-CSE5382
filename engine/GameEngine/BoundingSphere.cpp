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

bool BoundingSphere::Intersects(BoundingSphere s){
    //distance between centers greater than sum of radii?
    //yes:intersection
    float distance = boundCenter.distance(s.boundCenter);
    float radii = boundRadius + s.boundRadius;
    
    if( distance > radii )
        return true;
    else
        return false;
}

BoundingSphere::BoundingSphere(Vector3 center, float radius){
    this->boundRadius = radius;
    this->boundCenter = center;
}
BoundingSphere::BoundingSphere(vector<float> vertices){
    //find minX, maxX, repeat for Y and Z
    //use midpoint to find center
    //difference between midpoint and max||min is radius
    
    float maxX, maxY, maxZ;
    maxX = maxY = maxZ = std::numeric_limits<float>::min();
    float minX, minY, minZ;
    minX = minY = minZ = std::numeric_limits<float>::max();
    
    for(int i=0;i<3;i++){
        
        float x = 3*i;
        float y = (3*i) + 1;
        float z = (3*i) + 2;
        
        if( x > maxX )
            maxX = x;
        else if( x < minX )
            minX = x;
        
        if( y > maxY )
            maxY = y;
        else if( y < minY )
            minY = y;
        
        if( z > maxZ )
            maxZ = z;
        else if( z < minZ )
            minZ = z;
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