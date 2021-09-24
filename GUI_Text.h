#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

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
#include "Texture.h"
#include <vector>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif // BUFFER_OFFSET

class GUI_Text
{
public:
    GUI_Text();
    GUI_Text(const std::string texte,const glm::vec3 pointHautGauche, const glm::vec3 pointBasDroit);
    ~GUI_Text();
    void charger();
    void afficher(Texture &texture,const glm::mat4 &projection, const Shader &shader);
    void show(const bool show);
    std::string getText() const;
protected:
    std::string mText;
    float mVertices[1800];
    float mCoordTexture[1200];
    int mTailleVerticesBytes;
    int mTailleCoordTextureBytes;
    int mNbVertices;
    bool mShow;
    GLuint mVboID;
    GLuint mVaoID;
};

#endif // TEXT_H_INCLUDED
