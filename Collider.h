#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>

class Collider3D
{
public:
    Collider3D();
    Collider3D(std::string name,std::string forme, glm::vec3 meshPosition);
    Collider3D(std::string name,std::string forme,glm::vec3 meshPosition,glm::vec3 taille,glm::vec3 decalage);
    ~Collider3D();

    void setRectSize(glm::vec3 taille,glm::vec3 decalage);
    void setSphereRadius(float radius);
    void setName(std::string newName);

    void actualizePosition(glm::vec3 newPosition);
    bool checkRayCollision(glm::vec3 raySart,glm::vec3 rayEnd);

    glm::vec3 getHitRayPosition() const;
    glm::vec3 getPosition() const;
    std::string getName() const;

private:
    std::string mName;
    std::string mForme;
    glm::vec3 mTaille;
    glm::vec3 mDecalage;
    glm::vec3 mPosition;
    glm::vec3 mBoxPosition;
    glm::vec3 mLastCollide;
    glm::vec3 mCoinAvantDroitHaut;
    glm::vec3 mCoinAvantDroitBas;
    glm::vec3 mCoinAvantGaucheHaut;
    glm::vec3 mCoinAvantGaucheBas;
    glm::vec3 mCoinArriereDroitHaut;
    glm::vec3 mCoinArriereDroitBas;
    glm::vec3 mCoinArriereGaucheHaut;
    glm::vec3 mCoinArriereGaucheBas;
    glm::vec3 mNormalFaceAvant;
    glm::vec3 mNormalFaceArriere;
    glm::vec3 mNormalFaceHaut;
    glm::vec3 mNormalFaceBas;
    glm::vec3 mNormalFaceGauche;
    glm::vec3 mNormalFaceDroite;

    std::vector<float> equaPlan_a;
    std::vector<float> equaPlan_b;
    std::vector<float> equaPlan_c;
    std::vector<float> equaPlan_d;
    glm::vec2 equa_droite_x;
    glm::vec2 equa_droite_y;
    glm::vec2 equa_droite_z;
    std::vector<float> result;
    int mNearestResult;
    std::vector<glm::vec3> collidePoint;
    std::vector<glm::vec3> mRectArrayBis;
    float mRadius;

    struct Face
    {
        float equaPlan_a;
        float equaPlan_b;
        float equaPlan_c;
        float equaPlan_d;
        glm::vec3 normal;
    };

};

#endif // COLLIDER_H_INCLUDED
