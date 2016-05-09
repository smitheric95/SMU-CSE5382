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
    
    Ship& CreateShip(int i);
    Asteroid& CreateAsteroid(int i);
    Missile& CreateMissile(int i);
    void destroyAsteroid();
    
    vector<Missile*> allMissiles;
    vector<Asteroid*> allAsteroids;
    vector<Ship*> liveShips;
    
    //index,
    //asteroidNumber (index in allAsteroids),
    //rotation of missile
    vector< pair<int, Vector3> >hitAsteroids;
    
    int numAsteroids = 3;
    int numMissiles = 20;
    int numLives = 3;
    
    Ship* curShip;
    bool spacePressed;
    
    bool gameOver = false;
    bool lifeLost = false;
    
    void OnUpdate(const GameTime & time) override;
    void OnPreUpdate(const GameTime & time) override;
        
    
private:
    
};


#endif /* SimpleGame_hpp */
