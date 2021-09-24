#ifndef FOND_H_INCLUDED
#define FOND_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <cstring>
#include <string.h>

#include "Shaders.h"
#include "Texture.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif // BUFFER_OFFSET

class Fond
{
public:
    Fond(glm::vec3 position,std::string texture,std::string vertShader,std::string fragShader);
    ~Fond();
    void afficher(glm::mat4 projection,glm::mat4 modelview);
    void charger();

    void translate(glm::vec3 vecteur);
    void scale(glm::vec3 scale);
    void setPosition(glm::vec3 position);

    void setImgFile(std::string const &file);
    glm::vec3 getPosition() const;

private:
    Shader mShader;
    Texture mTexture;

    GLuint mVboID;
    GLuint mVaoID;

    float mVertices[18];
    float mCoordTexture[12];

    int mTailleVerticesBytes;
    int mTailleCoordTextureBytes;

    glm::vec3 mPosition;
    glm::vec3 mScale;
};

#endif // FOND_H_INCLUDED
