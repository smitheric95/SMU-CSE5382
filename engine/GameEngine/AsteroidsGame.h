//
//  SimpleGame.hpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Missile.h"

class AsteroidsGame : public Game
{
public:
	AsteroidsGame() : ShaderFolder("Shaders/")
    {
    }
    
    bool OnCreateScene() override;
    

    /// location of shaders in the file system.
	std::string ShaderFolder;
    
    Ship& CreateShip();
    Asteroid& CreateAsteroid();
    Missile& CreateMissile(int i);
    void destroyAsteroid();
    
    vector<Missile*> allMissiles;
    vector<Asteroid*> allAsteroids;
    //index, missileNumber, rotation of missile
    vector< pair<int, Vector3> >hitAsteroids;
    
    int numAsteroids = 1;
    int numMissiles = 20;
    
    Ship* curShip;
    bool spacePressed;
    
    bool gameOver = false;
    
    void OnUpdate(const GameTime & time) override;
    void OnPreUpdate(const GameTime & time) override;
        
    
private:
    
};


#endif /* SimpleGame_hpp */
