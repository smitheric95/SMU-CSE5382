#ifndef GEOMETRYPROVIDER_H
#define  GEOMETRYPROVIDER_H

#include "Common.h"
#include "Vectors.h"
#include "Matrix.h"

#include  <vector>


class GeometryProvider
{
public:
	/// abstract class 
	virtual ~GeometryProvider() = 0;

	static void Icosahedron(std::vector<Vector3>& vertices, std::vector<GLushort>& indices);
    //pass in vertices and indices
    //pass to mesh initialize
    //generating indices:
    /*
     
     01
     12
     23
     34
     45
     50
    
     for(i=0;i<vertices.size();i++)
        a = i;
        b = (i+1) % vertices.size();
     */
    

};

#endif
