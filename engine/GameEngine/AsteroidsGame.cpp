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
    
    for(int i=0;i<20;i++){
        allMissiles.push_back( CreateMissile() );
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
    

    asteroid.Transform.Translation = Vector3(rand()%20 + (-10), rand()%20 + (-10), 0);
    
    int scale = rand() % 2 + 1;
    asteroid.Transform.Scale = Vector3(scale, scale, scale);
    
    return asteroid;
}

Missile& AsteroidsGame::CreateMissile()
{
    auto& missile = Create<Missile>("missile");
    
    allMissiles.push_back(missile);
    
    return missile;
}

void AsteroidsGame::OnUpdate(const GameTime & time){
    Game curGame = Game::Instance();
    GLFWwindow* window = curGame.Window();
    
    /
        shooting all missiles at once instead of one
    /
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        Missile curMissile = allMissiles.front();
        allMissiles.pop_back();
        
        auto newPos = curMissile.Transform.GetMatrix();
        
        curMissile.Transform.Translation.X += 0.005 * newPos.m10;
        curMissile.Transform.Translation.Y += 0.005 * newPos.m11;
        curMissile.Transform.Translation.Z += 0.005 * newPos.m12;
    }
}

