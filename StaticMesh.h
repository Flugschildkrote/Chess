#ifndef STATICMESH_H_INCLUDED
#define STATICMESH_H_INCLUDED

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

#include "Cube.h"
#include "Texture.h"
#include "ObjDecoder.h"
#include "Animation.h"
#include "Collider.h"
#include <vector>

class Mesh
{
    public:

    Mesh(std::string name,float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture,std::string const modele3D);
    Mesh(const Mesh &meshACopier);
    ~Mesh();

    void afficher(glm::mat4 projection, glm::mat4 view);
    void charger();
    void updateVbo(void *donnees,int tailleBytes,int decalage);

    void addCollider3D(std::string colliderName,std::string forme,glm::vec3 taille,glm::vec3 decalage);
    bool checkRayCollision(glm::vec3 rayStart, glm::vec3 rayEnd, int hitBoxID);
    void actualizeColliderPosition(int hitboxID);

    glm::vec3 getHitRayPosition(int hitBoxID) const;
    Collider3D getCollider(int colliderID) const;
    std::vector<float> getVertices() const;
    glm::vec3 getPosition() const;
    glm::vec3 getColliderPosition(const int colliderID) const;
    std::string getName() const;
    int getNombreCollider() const;

    void translate(const glm::vec3 translation);
    void rotate(const float angle, const glm::vec3 axe);
    void scale(const glm::vec3 scale);
    void setPosition(const glm::vec3 newPosition);
    void setName(const std::string newName);
    void setAmbiantIntensity(const float intensity);
    void setTexture(const std::string newTexture);

    bool PlayAnim(int animation, int repetition);


    protected:

    glm::vec3 mPosition;
    glm::vec3 mScale;
    std::string mName;
    std::string mObjFile;
    int mNbVertices;
    int mNbAnimations;
    float mAmbiantIntensity;

    float mVertices[5000];
    float mCoordTexture[5000];
    float mNormals[5000];

    int mTailleVerticesBytes;
    int mTailleCoordTextureBytes;
    int mTailleNormalsBytes;

    OBJDecoder decoder;
    Texture mTexture;
    Shader mShader;
    GLuint mVboID;
    GLuint mVaoID;
    std::vector<Animation> mMeshAnims;
    std::vector<Collider3D> hitBox;

    std::vector<float> mVerticesBis;
    glm::mat4 modelview;
};

#endif // CAISSE_H_INCLUDED
