//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include <vector>
#include <iostream>

using namespace std;

#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"

#include <cmath>


bool AsteroidsGame::OnCreateScene()
{
    CreateShip();
    
    for(int i=0;i<20;i++){
        CreateAsteroid();
        
    }
    
    auto& cam = Game::Camera;
    
    cam.Transform.Translation.Z = 18;

    return true;
    
}

Ship& AsteroidsGame::CreateShip()
{
    auto& ship = Create<Ship>("ship");
    
    return ship;
}

Asteroid& AsteroidsGame::CreateAsteroid()
{
    auto& asteroid = Create<Asteroid>("asteroid");
    

    asteroid.Transform.Translation = Vector3(rand() % 20 + (-10), rand() % 20 + (-10), 0);
    
    asteroid.Transform.Translation.X += 0.005 * (float)(rand()% 4 + (-2));
    asteroid.Transform.Translation.Y += 0.005 * (float)(rand()% 4 + (-2));
    
    return asteroid;
}


