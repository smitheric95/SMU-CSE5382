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
    curShip = CreateShip();
    
    for(int i=0;i<20;i++){
        CreateAsteroid();
        
    }
    
    for(int i=0;i<10;i++){
        Missile cur = CreateMissile();
        cur.name = i;
        allMissiles.push_back( cur );
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
    
    return missile;
}

void AsteroidsGame::OnUpdate(const GameTime & time){
    Game curGame = Game::Instance();
    GLFWwindow* window = curGame.Window();
    
    if(!spacePressed && glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        spacePressed = true;
        Missile* curMissile = nullptr;

         for(int i=0;i<allMissiles.size();i++){
            if( !allMissiles[i].isActive ){
                curMissile = &allMissiles[i];
                std::cout << "allMissiles[i]: " << &allMissiles[i] << std::endl;
                break;
            }
        }
        
        if( curMissile != nullptr ){
            std::cout << "Missile #: " << curMissile->name << std::endl;
            std::cout << "---------" << std::endl;
            
            curMissile->isActive = true;
        }
        
    }
    else if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_RELEASE)
        spacePressed = false;
}

