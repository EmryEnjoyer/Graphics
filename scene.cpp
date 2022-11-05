// ================================================================= 
// Justice Roberts
// Homework #5
// CS 3233-01
// 9 November 2022
// =================================================================


#define _USE_MATH_DEFINES
#include <cmath>

#define PI 3.14159265358979323846

#include "UtilityFunctions.h"

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "camera.h"

#include "ObjectLoader.h"
#include "SceneObject.h"

#include "iostream"


struct imageData {
    unsigned char* data;
    int imgWidth, imgHeight, bytesPerPixel;
};

std::vector<imageData*> data;

void init()
{
    glEnable(GL_LIGHTING);    // Enable lighting.
    glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
    glEnable(GL_LIGHT1);      // Turn on a light. Use default light attributes.
    glEnable(GL_LIGHT2);      // Turn on a light. Use default light attributes.
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_TEXTURE_2D);
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);

    imageData * deskImage = new imageData;
    deskImage->data = stbi_load("wood.jpeg", 
                                 &deskImage->imgWidth, 
                                 &deskImage->imgHeight, 
                                 &deskImage->bytesPerPixel, 
                                 0);
    data.push_back(deskImage);

    imageData * typewriterProps = new imageData;
    typewriterProps->data = stbi_load("Typewriter Texture.png",
                                 &typewriterProps->imgWidth, 
                                 &typewriterProps->imgHeight, 
                                 &typewriterProps->bytesPerPixel, 
                                 0);
    data.push_back(typewriterProps);
}

void renderObj(const SceneObject & object)
{ 
    auto vertices = object.getVerts();
    auto uvs = object.getUvs();
    auto normals = object.getNormals();

    for(auto faces : object.getIndices())
    {
        glBegin(GL_TRIANGLE_FAN);  // We make the assumption that faces fall on a plane
        
        
        auto v0 = faces->vert[1][0];
        auto v1 = faces->vert[2][0];
        auto v2 = faces->vert[0][0];
            
        auto norm = computeNormal(
                vertices[v0],
                vertices[v1],
                vertices[v2]
            );
        for(auto indices : faces->vert) 
        {
            int vertexIndex = indices[0];
            int textureIndex = indices[1];
            int normalIndex = indices[2];

            if(textureIndex > 0)
            {
                glTexCoord2fv(uvs[textureIndex]);
            }
            
            glNormal3fv(
                norm
            );
            glVertex3fv(vertices[vertexIndex]);
        }
        delete [] norm;
        glEnd();
    }
}
void display()
{
    float color[3] = {1, 1, 1};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT, GL_SHININESS, color);
    
    SceneObject obj("Desk.obj", "wood.jpeg");
    
    
    SceneObject typeWriter("Typewriter.obj", "Typewriter Texture.png");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cameraSetLimits(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
    cameraApply();

    glPushMatrix();
    glScalef(10, 10, 10);
    glTexImage2D(GL_TEXTURE_2D, 
                0, 
                GL_RGB, 
                data[0]->imgWidth, 
                data[0]->imgHeight, 
                0, 
                GL_RGB, 
                GL_UNSIGNED_BYTE, 
                data[0]->data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    
    renderObj(obj);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5, 0);
    glScalef(2,2,2);
    glTexImage2D(GL_TEXTURE_2D, 
                0, 
                GL_RGBA, 
                data[1]->imgWidth, 
                data[1]->imgHeight,
                0, 
                GL_RGB, 
                GL_UNSIGNED_BYTE, 
                data[1]->data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP, GL_NEAREST);
    renderObj(typeWriter);
    glPopMatrix();

    glFlush();
}
int main (int argc, char ** argv)
{

    
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Indoor Scene");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}