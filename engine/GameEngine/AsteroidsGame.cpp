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
    curShip = &CreateShip();
    
    for(int i=0;i<20;i++){
        CreateAsteroid();
        
    }
    
    for(int i=0;i<30;i++){
        allMissiles.push_back( &CreateMissile(i) );
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

Missile& AsteroidsGame::CreateMissile(int i)
{
    auto& missile = Create<Missile>("missile");
    
    std::ostringstream sstream;
    sstream << "missile #" << i;
    missile.name = sstream.str();
    
    return missile;
}

void AsteroidsGame::OnPreUpdate(const GameTime & time){
    //take care of collisons
    /*
     loop thru ast, does transform.boudingSphere overlap bounding (trans.bounds) of missile/ship?
     */
    
    //for(int i=0;i<)
    //boundingsphere shipBounds = boundingsphere getTransBounds()
    
}

//logic for handling missiles
void AsteroidsGame::OnUpdate(const GameTime & time){
    Game curGame = Game::Instance();
    GLFWwindow* window = curGame.Window();

    //if the spacebar is pressed once
    if(!spacePressed && glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        spacePressed = true;
        Missile* curMissile = nullptr;
        
        //find the first inactive missile
        for(int i=0;i<allMissiles.size();i++){
            if( !allMissiles[i]->isActive ){
                curMissile = allMissiles[i];
                curMissile->Transform.Translation = curShip->Transform.Translation;
                curMissile->Transform.Rotation = curShip->Transform.Rotation;
                curMissile->hasBeenShot = false;
                curMissile->backToShip = false;
                break;
            }
        }
        
        //set the missile to active
        if( curMissile != nullptr ){
            
            curMissile->isActive = true;
        }
        
    }
    else if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_RELEASE)
        spacePressed = false;
}

