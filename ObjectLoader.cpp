// ================================================================= 
// Justice Roberts
// Homework #5
// CS 3233-01
// 9 November 2022
// =================================================================

#include "ObjectLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>

std::vector<std::string> splitByDelimiter(const std::string & line, char delimiter=' ')
{
    std::vector<std::string> words;

    std::string word = "";
    for(int i = 0; i < line.length(); ++i)
    {
        if(line[i] != delimiter)
            word = word + line[i];
        else
        {
            words.push_back(word);
            word = "";
        }
    }
    words.push_back(word);
    return words;
}

void loadObj(const char * path, 
             std::vector<float*> & verts, 
             std::vector<float*> & uvs, 
             std::vector<float*> & normals,
             std::vector<Face*> & faces)
{
    std::ifstream file(path);
    if(!file.is_open())
        std::cerr << "Error: Unable to open file " << path << ".";
    
    std::string line = "";
    while(std::getline(file, line))
    {
        if(line.length() <= 0) continue;

        std::vector<std::string> words = splitByDelimiter(line);
        if(words[0] == "v")
        {
            // v is followed by 3 floating point numbers separated by spaces.
            float * vert = new float[3];
            vert[0] = std::stof(words[1]);
            vert[1] = std::stof(words[2]);
            vert[2] = std::stof(words[3]);
            verts.push_back(vert);
        }

        if(words[0] == "vt")
        {
            // vf is followed by 2 floating point numbers separated by a space
            float * uv = new float[2];
            uv[0] = std::stof(words[1]);
            uv[1] = std::stof(words[2]);
            uvs.push_back(uv);
        }

        if(words[0] == "vn")
        {
            float * norm = new float[3];
            norm[0] = std::stof(words[1]);
            norm[1] = std::stof(words[2]);
            norm[2] = std::stof(words[3]);
            normals.push_back(norm);
        }

        if(words[0] == "f")
        {
            // f followed by 3 sets of faces
            // index sets lengths between 1 and 3.
            // <v[/[vt][/vn]]>
            std::vector<std::string> indexLists;

            for(int i = 1; i < words.size(); ++i)
                indexLists.push_back(words[i]);

            Face * f = new Face;

            for(auto indexList : indexLists) 
            {
                
                int * temp_faces = new int[3];
                auto ind = splitByDelimiter(indexList, '/');
                for(int i = 0; i < 3; ++i)
                {
                    if(ind[i] != "")
                        temp_faces[i] = std::stoi(ind[i]) - 1;
                    else
                        temp_faces[i] = -1;
                }
                f->vert.push_back(temp_faces);
            }

            faces.push_back(f);
        }
    }
}

