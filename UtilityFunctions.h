#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>

#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
/**
 * Creates a new array containing n evenly spaced pairs of x,y coordinates
 * on a circle of radius r with center (0,0)
 * @param numPoints: number of points
 * @param center: 2d center of points
 * @param radius: radius of circle
 * @returns: std::pair array containing x and y coordinates. 
 * Ownership is transferred to the calling function.
 **/
std::pair<double, double> * RegularPolyPoints(int numPoints, double* center, double radius); 


/** Computes a normal vector and returns it. Ownwership passed back to caller
  * @param p1: First point in tri
  * @param p2: Second point in tri
  * @param p3: Third point in tri
  **/ 
float * computeNormal(float * p1, float * p2, float * p3);

#endif