#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "string.h"
#include "cstring"

#include "Shaders.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif // BUFFER_OFFSET

class cube
{
public:
    cube(float taille,std::string const vertexShader,std::string const fragmentShader);
    ~cube();
    void afficher(glm::mat4 projection,glm::mat4 modelview);
    void charger();
    void updateVbo(void *donnees,int tailleBytes,int decalage);
protected:
    Shader mShader;
    float mVertices[108];
    float mCouleurs[108];
    GLuint mVboID;
    GLuint mVaoID;
    int mTailleVerticesBytes;
    int mTailleCouleursBytes;
};

#endif // CUBE_H_INCLUDED
