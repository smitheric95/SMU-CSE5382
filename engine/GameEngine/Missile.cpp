//
//  Missile.cpp
//  GameEngine
//
//  Created by David Lively on 4/11/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Missile.h"

#include "Common.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

using namespace std;

bool Missile::OnInitialize()
{
    //call parent mesh thing
    auto& mesh = Create<Mesh>("missile-mesh");
    
    
    /// narrow triangle pointed along the positive Y axis
    vector<float> vertices =
    {
        0,0.5f, 0
        ,
        0, -0.5f, 0
        ,
        0, -0.5f, 0
    };
    
    
    vector<GLushort> indices = {0,1,2};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;

    
    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    mesh.Type = BeginMode::Lines;
        
    return material.Build("Shaders/primitive");
}

void Missile::OnUpdate(const GameTime& time)
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
    
    if(!hasBeenShot && glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS){
        auto newPos = Transform.GetMatrix();
        
        Transform.Translation.X += 0.005 * newPos.m10;
        Transform.Translation.Y += 0.005 * newPos.m11;
        Transform.Translation.Z += 0.005 * newPos.m12;
    }
    
    if((!hasBeenShot || !isActive) && glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS){
        Transform.Rotation.Z += 0.1;
    }
    
    if((!hasBeenShot || !isActive) && glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS){
        Transform.Rotation.Z -= 0.1;
    }
    
    if(isActive && glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        
        hasBeenShot = true;
        
        std::cout << "FIRE MISSILE!" << std::endl;
        auto newPos = Transform.GetMatrix();
        
        Transform.Translation.X += 0.005 * newPos.m10;
        Transform.Translation.Y += 0.005 * newPos.m11;
        Transform.Translation.Z += 0.005 * newPos.m12;
    }
    
}


void Missile::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

float Missile::getPreviousFrameTime(){
    return previousFrameTime;
}
void Missile::setPreviousFrameTime(float previousFrameTime){
    this->previousFrameTime = previousFrameTime;
}

