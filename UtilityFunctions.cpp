#include "UtilityFunctions.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

std::pair<double, double> * RegularPolyPoints(int numPoints, double* center, double radius) 
{
    std::pair<double, double> * coordinates = new std::pair<double,double>[numPoints];
    for(int i = 0; i < numPoints; ++i) 
    {
        coordinates[i] = std::pair<double, double>(
            center[0] + radius * cos(2 * M_PI * i / numPoints),
            center[1] + radius * sin(2 * M_PI * i / numPoints)
        );
    }
    return coordinates;
}

float * computeNormal(float * p1, float * p2, float * p3)
{
    float v[3] = {
        p2[0] - p1[0],
        p2[1] - p1[1],
        p2[2] - p1[2], 
    };
    
    float w[3] = {
        p3[0] - p1[0],
        p3[1] - p1[1],
        p3[2] - p1[2],
    };
    float * u = new float[3];
    u[0] = v[1] * w[2] - v[2] * w[1];
    u[1] = v[2] * w[0] - v[0] * w[2];
    u[2] = v[0] * w[1] - v[1] * w[0];
    return u;
}
