#include "SceneOpenGL.h"

using namespace glm;

SceneOpenGL::SceneOpenGL(std::string windowName,int largeur,int hauteur):mWindowName(windowName),mLargeur(largeur),mHauteur(hauteur),mInput()
{

}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(mGLContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

bool SceneOpenGL::initializeWindow()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

    mWindow = SDL_CreateWindow(mWindowName.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,mLargeur,mHauteur,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(mWindow == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    mGLContext = SDL_GL_CreateContext(mWindow);

    if(mGLContext == 0)
    {
        std::cout << "Ipossible de creer le contexte OpenGL : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mWindow);
        SDL_Quit();

        return false;
    }

    if(SDL_GL_SetSwapInterval(1) < 0)
    {
        std::cout << "Impossible d'activer le synchro verticale :" << SDL_GetError() << std::endl;
    }

    return true;
}


bool SceneOpenGL::initGL()
{
 

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Erreur lors de l'initialisation de GLAD" << std::endl;
        SDL_GL_DeleteContext(mGLContext);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();

        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.7f, 1.0f, 0.0f);

    return true;
}

void SceneOpenGL::go()
{
    mat4 projection;
    mat4 view;

    Camera camera(vec3(0,1,1),vec3(0,0,0),vec3(0,1,0),0.2,0.2);
    mInput.lockCursor(false);
    mInput.showCursor(true);

    projection = perspective(70.0, (double) mLargeur / mHauteur, 1.0, 100.0);
    view = mat4(1.0);

    GameManager gameManager;

    unsigned int framerate = 1000/60;
    Uint32 debutBoucle(0),finBoucle(0),tempsEcoule(0);

    int mouseX;
    int mouseY;
    bool clicked = false;

    while(!mInput.quit())
    {
        debutBoucle = SDL_GetTicks();

        mInput.uptdateEvent();
        if(mInput.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.deplacerCHESS(mInput,10);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.lookAt(view);


        mouseX = mInput.getX();
        mouseY = mHauteur - mInput.getY();
        glm::vec3 vect1 = glm::unProject(glm::vec3(mouseX,mouseY,0.0),view,projection,glm::vec4(0,0,mLargeur,mHauteur));
        glm::vec3 vect2 = glm::unProject(glm::vec3(mouseX,mouseY,1.0),view,projection,glm::vec4(0,0,mLargeur,mHauteur));

        if(mInput.getKey(SDL_SCANCODE_Q))
        {
            if(!clicked)
                gameManager.passerTour();
            clicked = true;
        }
        else{clicked = false;};
        gameManager.play(mInput.getMouseButton(1),vect1,vect2);
        gameManager.drawScene(projection,view);
        //guiManager.afficher(view);
        //std::cout << tour2.getState() << std::endl;

       /* if(mesh.checkRayCollision(vect1,vect2,0))
        {
            std::cout << mesh.getCollider(0).getName() << std::endl;
        }
        else
        {
            std::cout << "0" << std::endl;
        }
        if(mesh.checkRayCollision(vect1,vect2,1))
        {
            std::cout << mesh.getCollider(1).getName() << std::endl;
        }
        else
        {
            std::cout << "0" << std::endl;
        }*/
        //std::cout << mesh.getHitRayPosition(0).x << ";" << mesh.getHitRayPosition(0).y << ";" << mesh.getHitRayPosition(0).z << std::endl;

        SDL_GL_SwapWindow(mWindow);

        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle-debutBoucle;

        if(tempsEcoule < framerate)
            SDL_Delay(framerate - tempsEcoule);
        //std::cout << (float)tempsEcoule << std::endl;
    }
}

int SceneOpenGL::getLargeur() const
{
    return mLargeur;
}

int SceneOpenGL::getHauteur() const
{
    return mHauteur;
}
