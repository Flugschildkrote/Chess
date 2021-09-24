#include "Terrain.h"

Terrain::Terrain()
{
    mMesh = new Mesh("Terrain",1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag","terrain.png","terrain.obj");
    mMesh->charger();
    mMesh->addCollider3D("terrain_Main","RECT",glm::vec3(16,1,16),glm::vec3(0,0.5,0));
    mMesh->addCollider3D("terrain_cote_droit","RECT",glm::vec3(1,1.5,16),glm::vec3(8.5,0.75,0));
    mMesh->addCollider3D("terrain_cote_gauche","RECT",glm::vec3(1,1.5,16),glm::vec3(-8.5,0.75,0));
    mMesh->addCollider3D("terrain_cote_avant","RECT",glm::vec3(18,1.5,1),glm::vec3(0,0.75,-8.5));
    mMesh->addCollider3D("terrain_cote_arriere","RECT",glm::vec3(18,1.5,1),glm::vec3(0,0.75,8.5));
}

Terrain::~Terrain()
{
    delete mMesh;
}

void Terrain::setPosition(const glm::vec3 newPosition)
{
    mMesh->setPosition(newPosition);
    for(int i(0); i < 5; i++)
        mMesh->actualizeColliderPosition(i);
}

void Terrain::translate(const glm::vec3 translation)
{
    mMesh->translate(translation);
    for(int i(0); i < 5; i++)
        mMesh->actualizeColliderPosition(i);

}

void Terrain::rotate(const float angle, const glm::vec3 axe)
{
    mMesh->rotate(angle,axe);
}

void Terrain::scale(const glm::vec3 scale)
{
    mMesh->scale(scale);
}

void Terrain::afficher(glm::mat4 projection, glm::mat4 view)
{
    mMesh->afficher(projection, view);
    glm::vec3 pos = mMesh->getPosition();
    glm::vec3 pos2 = mMesh->getColliderPosition(0);
}

Collider3D Terrain::getCollider(const int id) const
{
    return mMesh->getCollider(id);
}

std::string Terrain::getName() const
{
    return mMesh->getName();
}

void Terrain::setIntensity(const float intensity)
{
    mMesh->setAmbiantIntensity(intensity);
}
