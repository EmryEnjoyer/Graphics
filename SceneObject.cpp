#include "SceneObject.h"
#include "ObjectLoader.h"
#include <string>

SceneObject::SceneObject(std::string objFile, std::string texFile)
{
    this->objFile = objFile;
    this->texFile = texFile;
    loadObj(objFile.c_str(), verts, uvs, normals, indices);
}

std::vector<float*> SceneObject::getVerts() const { return verts; }
std::vector<float*> SceneObject::getUvs() const { return uvs; }
std::vector<float*> SceneObject::getNormals() const { return normals; }
std::vector<Face*> SceneObject::getIndices() const { return indices; }
std::string SceneObject::getTexFile() const { return texFile; }

SceneObject::~SceneObject()
{
    for(auto vert : verts)
        delete [] vert;
    for(auto uv : uvs)
        delete [] uv;
    for(auto norm : normals)
        delete [] norm;
    for(auto f : indices)
    {
        for(auto ind : f->vert)
            delete [] ind;
        delete f;
    }
}