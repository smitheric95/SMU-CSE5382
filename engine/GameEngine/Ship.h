//
//  Ship.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef SHIP_H
#define SHIP_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"

class Ship : public WorldEntity
{
public:
    
    Ship()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    Vector3 currentTranslation, previousTranslation;
    
//    BoundingSphere bounds;
    
    bool hasSwitchedX = false;
    bool hasSwitchedY = false;
    bool canMove = true;
    int lifeNumber;
    bool hasBeenPushed = false;
    
    float previousFrameTime = 0.001f;
    float getPreviousFrameTime();
    void setPreviousFrameTime( float previousFrameTime );
    
private:
    Mesh* m_mesh;
    Material* m_material;
    
};


#endif /* Ship_hpp */
