//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"

#include <cmath>


bool AsteroidsGame::OnCreateScene()
{
    //ship that flies around
    curShip = &CreateShip(-1);
    
    //ships for lives
    for(int i=0;i<numLives;i++)
        liveShips.push_back( &CreateShip(i) );
    
    for(int i=0;i<numAsteroids;i++)
        allAsteroids.push_back( &CreateAsteroid(i) );
    
    for(int i=0;i<numMissiles;i++)
        allMissiles.push_back( &CreateMissile(i) );
    
    auto& cam = Game::Camera;
    
    cam.Transform.Translation.Z = 18;

    return true;
    
}

Ship& AsteroidsGame::CreateShip(int i)
{
    auto& ship = Create<Ship>("ship");
    
    ship.lifeNumber = i;

    return ship;
}

Asteroid& AsteroidsGame::CreateAsteroid(int i)
{
    auto& asteroid = Create<Asteroid>("asteroid");
    
    //place asteroids away from ship (-1 to 1)
    int randomDecider = rand() % 2;
    
    if(randomDecider == 1)
        asteroid.Transform.Translation = Vector3(rand()%5+1, rand()%5+1, 0);
    else
        asteroid.Transform.Translation = Vector3((rand()%5+1)*-1, (rand()%5+1)*-1, 0);
    
    if(i < levelNumAsteroids ){
        int scale = rand() % 2 + 1;
        asteroid.Transform.Scale = Vector3(scale, scale, scale);
    }
    else{
        asteroid.isActive = false;
        asteroid.Transform.Scale = 0;
    }
    
    asteroid.ID = i;
    
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

void AsteroidsGame::destroyAsteroid(){
    for(int i=0;i<hitAsteroids.size();i++){
        
        int first = hitAsteroids[i].first;
        
        if( !allAsteroids[first]->hasSwitchedX && !allAsteroids[first]->hasSwitchedY  ){
            allAsteroids[first]->Transform.Rotation = hitAsteroids[i].second * -1;
            allAsteroids[first]->Transform.Translation *= 1.0005;
        }
        else{
            allAsteroids[first]->isActive = false;
            allAsteroids[first]->Transform.Scale = 0;
        }
    }
}

void AsteroidsGame::OnPreUpdate(const GameTime & time){
    if( !gameOver ){
        //take care of collisons
        BoundingSphere shipBounds = curShip->getTransformedBounds();
        
        for(int i=0;i<numAsteroids;i++){
            BoundingSphere temp = allAsteroids[i]->getTransformedBounds();
            
            //asteroid hits ship
            if( temp.Intersects(shipBounds) && allAsteroids[i]->isActive ){
                
                numLives--;
                
                //kill life ship
                Ship* curLiveShip = liveShips.back();
                liveShips.pop_back();
                curLiveShip->hasBeenPushed = true;
                
                
                lifeLost = true;
                
                break;
            }
            
            for(int j=0;j<numMissiles;j++){
                BoundingSphere missileBounds = allMissiles[j]->getTransformedBounds();
                
                //missile hits asteroid
                if( temp.Intersects(missileBounds) && allMissiles[j]->isActive && allAsteroids[i]->isActive ){
                    pair<int, Vector3> ast = make_pair(i, allMissiles[j]->Transform.Rotation);
                    
                    //add asteroid to hitAteroids if its not already there
                    
                    //O(n^3) woo hoo!
                    
                    bool addAsteroid = true;
                    for(int k=0;k<hitAsteroids.size();k++){
                        if( i == hitAsteroids[k].first )
                            addAsteroid = false;
                    }
                    
                    if(addAsteroid)
                        hitAsteroids.push_back(ast);
                }
            }
        }
    }
}

//logic for handling missiles
void AsteroidsGame::OnUpdate(const GameTime & time){
    Game curGame = Game::Instance();
    GLFWwindow* window = curGame.Window();
    
    if( !lifeLost && !gameOver ){
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
        
        destroyAsteroid();
        
        if( hitAsteroids.size() == numAsteroids ){
            std::cout << "You win!" << std::endl;
            gameOver = true;
        }
        //start new level
        else if( hitAsteroids.size() == levelNumAsteroids ){
            //make hit asteroids inactive
            for(int i=0;i<hitAsteroids.size();i++){
                allAsteroids[ hitAsteroids[i].first ]->shotOut = true;
            }
            
            for(int i=levelNumAsteroids;i<levelNumAsteroids+levelIncrement;i++){
                //place asteroids away from ship (-1 to 1)
                int scale = rand() % 2 + 1;
                allAsteroids[i]->Transform.Scale = Vector3(scale, scale, scale);
                allAsteroids[i]->speed = 0.05;
                allAsteroids[i]->isActive = true;
            }
            
            levelNumAsteroids += levelIncrement;
            
        }
        
    }
    else{
        //reset ship to center after certain time
        curShip->Transform.Translation = Vector3(0,0,0);
        curShip->previousTranslation = Vector3(0,0,0);
        
        Missile* curMissile = nullptr;
        
        for(int i=0;i<allMissiles.size();i++){
            curMissile = allMissiles[i];
            curMissile->Transform.Translation = Vector3(0,0,0);
            curMissile->previousTranslation = Vector3(0,0,0);
            curMissile->Transform.Rotation = curShip->Transform.Rotation;
            curMissile->isActive = false;
            curMissile->hasBeenShot = false;
            
            if(liveShips.size() < 1 )
                curMissile->canMove = false;
        }
        
        lifeLost = false;
        
        if(liveShips.size() < 1 ){
            curShip->canMove = false;
            gameOver = true;
        }
    }
}

