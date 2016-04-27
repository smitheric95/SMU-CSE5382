//
//  Ship.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "Ship.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

using namespace std;

bool Ship::OnInitialize()
{
    auto& mesh = Create<Mesh>("ship-mesh");
    
    
    /// narrow triangle pointed along the positive Y axis
    vector<float> vertices =
    {
        0,0.5f, 0
        ,
        1/3.f, -0.5f, 0
        ,
        -1/3.f, -0.5f, 0
    };
    
    vector<GLushort> indices = {0,1,2};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    //set up bounding sphere - from verts of ship, ast, missiles
    Bounds = BoundingSphere(vertices);
    
    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    
    return material.Build("Shaders/primitive");
}

void Ship::OnUpdate(const GameTime& time)
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
    
    float drag = 0.015;
    
    //prev = cur at beginning of each frame
    previousTranslation = currentTranslation;
    
    Transform.Translation = currentTranslation;
    
    Transform.Translation += velocity * (1 - drag);
    
    if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS){
        auto newPos = Transform.GetMatrix();
        
        /*
        Bounds.matrix.X += 0.005 * newPos.m10;
        Bounds.matrix.Y += 0.005 * newPos.m11;
        Bounds.matrix.Z += 0.005 * newPos.m12;
        */
        
        Transform.Translation.X += 0.005 * newPos.m10;
        Transform.Translation.Y += 0.005 * newPos.m11;
        Transform.Translation.Z += 0.005 * newPos.m12;
    }
    
    if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS){
        Transform.Rotation.Z += 0.1;
    }
    
    if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS){
        Transform.Rotation.Z -= 0.1;
    }
    
}


void Ship::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

float Ship::getPreviousFrameTime(){
    return previousFrameTime;
}
void Ship::setPreviousFrameTime(float previousFrameTime){
    this->previousFrameTime = previousFrameTime;
}

