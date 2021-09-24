#ifndef SCENEOPENGL_H_INCLUDED
#define SCENEOPENGL_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <iostream>
#include <string.h>

#include "Input.h"
#include "Texture.h"
#include "Fond.h"
#include "StaticMesh.h"
#include "Cube.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Tour.h"
#include "Roi.h"
#include "Pion.h"
#include "Reine.h"
#include "Cavalier.h"
#include "Fou.h"
#include "GameManager.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class SceneOpenGL
{
public:
    SceneOpenGL(std::string windowName,int largeur,int hauteur);
    ~SceneOpenGL();

    bool initializeWindow();
    bool initGL();

    int getLargeur() const;
    int getHauteur() const;

    void go();

private:
    std::string mWindowName;
    int mLargeur;
    int mHauteur;

    SDL_Window *mWindow;
    SDL_GLContext mGLContext;
    Input mInput;
};

#endif // SCENEOPENGL_H_INCLUDED
