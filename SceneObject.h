// ================================================================= 
// This code represents an object in the scene.
// It's used to abstract away loading objects.
// Justice Roberts
// Homework #5
// CS 3233-01
// 9 November 2022
// =================================================================

#include <vector>
#include <string>

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

/**
 * @brief Wraps a vector for a layer of abstraction
 **/
struct Face
{
    std::vector<int*> vert;    // Vector of [Vertex, Texture, Normal] indices
};

class SceneObject 
{
std::string objFile;
std::string texFile;

std::vector<float*> verts, uvs, normals;
std::vector<Face*> indices;

public:
    SceneObject(std::string objFile, std::string texFile="");
    std::vector<float*> getVerts() const;
    std::vector<float*> getUvs() const;
    std::vector<float*> getNormals() const;
    std::vector<Face*> getIndices() const;
    std::string getTexFile() const;
    ~SceneObject();
};
#endif