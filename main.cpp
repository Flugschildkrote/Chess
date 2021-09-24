#include "SceneOpenGL.h"

int main(int argc, char **argv)
{
    SceneOpenGL scene("Pong",800,600);

    if(!scene.initializeWindow())
        return -1;

    if(!scene.initGL())
        return -1;

    scene.go();

    return 0;
}
