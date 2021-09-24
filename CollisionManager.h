#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <math.h>

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
#include "Collider.h"

class CollisionManager
{
public :
    CollisionManager();
    ~CollisionManager();
    void add3DCollider(Collider3D collider);
    void actualizeCollider(Collider3D collider);
    std::string checkNearestCollision(glm::vec3 rayStart, glm::vec3 rayEnd);
    int getNbCollider() const;
    glm::vec3 getHitPosition();
private:
    std::vector<Collider3D> m3DColliders;
    std::vector<Collider3D> m3DCollidersHit;
    std::vector<float> mNormes;
    std::string mLastColliderName;
};

#endif // COLLISIONMANAGER_H_INCLUDED
