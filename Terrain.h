#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "StaticMesh.h"

class Terrain
{
public:
    Terrain();
    ~Terrain();
    void setPosition(const glm::vec3 newPosition);
    void translate(const glm::vec3 translation);
    void rotate(const float angle, const glm::vec3 axe);
    void scale(const glm::vec3 scale);

    void afficher(glm::mat4 projection, glm::mat4 view);

    Collider3D getCollider(const int id) const;
    std::string getName() const;

    void setIntensity(const float intensity);

protected:
    Mesh *mMesh;
};
#endif // TERRAIN_H_INCLUDED
