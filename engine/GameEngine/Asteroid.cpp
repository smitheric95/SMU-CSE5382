//
//  Asteroid.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Asteroid.h"

#include "Common.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

using namespace std;

bool Asteroid::OnInitialize()
{
    //call parent mesh thing
    auto& mesh = Create<Mesh>("ship-mesh");
    
    

    vector<Vector3> vertices;
    vector<GLushort> indices;
    
    int segments = 6;
    float dTheta = 360/segments;

    for(int i=0; i<6; i++){
        GLushort a = i;
        GLushort b = (i+1) % segments;
        
        indices.push_back(a);
        indices.push_back(b);
    }
    
    for(int theta=0; theta<360; theta+=dTheta){
        float x = cos(TO_RADIANS(theta));
        float y = sin(TO_RADIANS(theta));
        
        Vector3 v(x,y,0);
        vertices.push_back(v);
    }
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    Bounds = BoundingSphere(vertices);
    
    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    mesh.Type = BeginMode::Lines;
    
    
    return material.Build("Shaders/primitive");
}

void Asteroid::OnUpdate(const GameTime& time)
{
    Game curGame = Game::Instance();
    GLFWwindow* window = curGame.Window();
    
    currentTranslation = Transform.Translation;
    
    auto& cam = Game::Camera;
    Matrix camMatrix = cam.Transform.GetMatrix();
    Matrix aspectRatio = cam.GetProjectionMatrix();
    
    //calculate width and height of
    float halfWidth = camMatrix.m32 / aspectRatio.m00;
    float halfHeight = camMatrix.m32 / aspectRatio.m11;
    
    currentTranslation = Transform.Translation;
    
    if( (currentTranslation.X < (-1*halfWidth) || currentTranslation.X > halfWidth) && !hasSwitchedX ){
        
        if( previousTranslation.X < 0 )
            previousTranslation.X -= 2*(abs(currentTranslation.X) - abs(previousTranslation.X));
        else if( previousTranslation.X > 0 )
            previousTranslation.X += 2*(abs(currentTranslation.X) - abs(previousTranslation.X));
        
        previousTranslation.X *= -1;
        currentTranslation.X *= -1;
        hasSwitchedX = true;
    }
    else if(currentTranslation.X > (-1*halfWidth) && currentTranslation.X < (halfWidth)){
        hasSwitchedX = false;
    }
    
    if( (currentTranslation.Y < (-1*halfHeight) || currentTranslation.Y > halfHeight) && !hasSwitchedY ){
        
        if( previousTranslation.Y < 0 )
            previousTranslation.Y -= 2*(abs(currentTranslation.Y) - abs(previousTranslation.Y));
        else if( previousTranslation.Y > 0 )
            previousTranslation.Y += 2*(abs(currentTranslation.Y) - abs(previousTranslation.Y));
        
        previousTranslation.Y *= -1;
        currentTranslation.Y *= -1;
        hasSwitchedY = true;
    }
    else if(currentTranslation.Y > (-1*halfHeight) && currentTranslation.Y < (halfHeight)){
        hasSwitchedY = false;
    }
    
    
    
    //calculate dt
    float timeScale = time.ElapsedSeconds() / getPreviousFrameTime();
    if( time.ElapsedSeconds() / getPreviousFrameTime() > 0 )
        setPreviousFrameTime( time.ElapsedSeconds() );
    
    //find velocity
    Vector3 velocity = (currentTranslation - previousTranslation) * timeScale;
    
    
    //prev = cur at beginning of each frame
    previousTranslation = currentTranslation;
    
    Transform.Translation = currentTranslation;
    
    Transform.Translation += velocity;
    
    if( !hasBeenPushed ){
        Transform.Translation.X += 0.0005 * (rand() % 3 + (-1));
        Transform.Translation.Y += 0.0005 * (rand() % 3 + (-1));
        
        //Bounds.matrix.X += 0.0005 * (rand() % 3 + (-1));
        //Bounds.matrix.Y += 0.0005 * (rand() % 3 + (-1));
        
        hasBeenPushed = true;
    }
    
}


void Asteroid::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

float Asteroid::getPreviousFrameTime(){
    return previousFrameTime;
}
void Asteroid::setPreviousFrameTime(float previousFrameTime){
    this->previousFrameTime = previousFrameTime;
}

