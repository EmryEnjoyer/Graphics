// =================================================================
// This code loads a .obj file and interprets it as vertices,
// faces, and UV vertices. I built this from the .obj file
// specification. The tutorial below also served as a guide.
// 
// Notes:
//   1. This code does not provide a method to read polylines or bezier curves (yet)
//   2. This code requires all models to be triangulated.
//   3. The intent is for this code to be able to read models made in Blender
//
// Tutorial: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// File spec: https://en.wikipedia.org/wiki/Wavefront_.obj_file#File_format
// 
// Justice Roberts
// Homework #5
// CS 3233-01
// 9 November 2022
// =================================================================
#include <vector>
#include "SceneObject.h"

#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H
/**
 * Loads a .obj file into vert, uv, and normal. On error, writes problem to cerr.
 * 
 * @param vert: Vector of 3x1 matrices representing vectors
 * @param uv: Vector of 2x1 matrices repreenting texture coordinates
 * @param normal: Vector of 3x1 matrices representing normal vectors
 **/
void loadObj(const char * path, 
             std::vector<float*> & verts, 
             std::vector<float*> & uvs, 
             std::vector<float*> & normals,
             std::vector<Face*> & indices);
#endif