//
//  Missile.h
//  GameEngine
//
//  Created by Eric Smith on 4/11/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef Missile_h
#define Missile_h

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"

class Missile : public WorldEntity
{
public:
    
    Missile()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    Vector3 currentTranslation, previousTranslation;
    
    bool hasSwitchedX = false;
    bool hasSwitchedY = false;
    bool hasBeenPushed = false;
    
    float previousFrameTime = 0.001f;
    float getPreviousFrameTime();
    void setPreviousFrameTime( float previousFrameTime );
    
private:
    Mesh* m_mesh;
    Material* m_material;
    
};
#endif /* Missile_h */
