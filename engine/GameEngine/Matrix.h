//
//  Matrix.hpp
//  GameEngine
//
//  Created by David Lively on 2/10/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef MATRIX_H
#define MATRIX_H

#include "Vectors.h"
#include <iostream>

using namespace std;
class Matrix
{
public:
    /// X basis vector
    float m00, m01, m02, m03;
    /// y basis vector
    float m10, m11, m12, m13;
    /// z basis vector
    float m20, m21, m22, m23;
    /// translation
    float m30, m31, m32, m33;
    
    Matrix() :
    m00(1), m01(0), m02(0), m03(0)
    ,m10(0), m11(1), m12(0), m13(0)
    ,m20(0), m21(0), m22(1), m23(0)
    ,m30(0), m31(0), m32(0), m33(1)
    {
        
    }
    
    
    static Matrix Identity();
    static void CreateRotationX(Matrix& m, float radians);
    static void CreateRotationY(Matrix& m, float radians);
    static void CreateRotationZ(Matrix& m, float radians);
    
    
    static Matrix CreateRotationX(float radians);
    static Matrix CreateRotationY(float radians);
    static Matrix CreateRotationZ(float radians);
    
    static Matrix CreateRotation(float x, float y, float z);
    static Matrix CreateRotation(const Vector3& rotate);
    static Matrix CreateTranslation(float x, float y, float z);
    static Matrix CreateTranslation(const Vector3& position);
    
    static Matrix CreateScale(float x, float y, float z);
    static Matrix CreateScale(float uniformScale);
    static Matrix CreateScale(const Vector3& scale);
    
    static Matrix CreatePerspective(float fov, float aspect, float zNear, float zFar);
  
    

    
    static void Multiply(const Matrix& left, const Matrix& right, Matrix& result);
    
    static Matrix Multiply(const Matrix& left, const Matrix& right)
    {
        Matrix result;
        
        Multiply(left, right, result);
        
        return result;
    }
    
    Matrix operator*(const Matrix& right)
    {
        return Multiply(*this, right);
    }
    
    Vector4 operator*(const Vector4 &v){
        Vector4 vPrime;
        
        vPrime.X = (v.X * m00) + (v.Y * m01) + (v.Z * m02) + (v.W * m03);
        vPrime.Y = (v.X * m10) + (v.Y * m11) + (v.Z * m12) + (v.W * m13);
        vPrime.Z = (v.X * m20) + (v.Y * m21) + (v.Z * m22) + (v.W * m23);
        vPrime.W = (v.X * m30) + (v.Y * m31) + (v.Z * m32) + (v.W * m33);
        
        
        return vPrime;
    }
    
    Vector3 operator*(const Vector3 &v){
        Vector3 vPrime;
        
        float w = 1.f;
        
        vPrime.X = (v.X * m00) + (v.Y * m10) + (v.Z * m20) + (w * m30);
        vPrime.Y = (v.X * m01) + (v.Y * m11) + (v.Z * m21) + (w * m31);
        vPrime.Z = (v.X * m02) + (v.Y * m12) + (v.Z * m22) + (w * m32);
        
        
        return vPrime;
    }
    
    
    
    friend ostream& operator<<(ostream& out, const Matrix& m);
    
    
private:
};

#endif /* Matrix_hpp */








