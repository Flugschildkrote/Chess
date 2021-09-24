#include "CollisionManager.h"

CollisionManager::CollisionManager(){ }

CollisionManager::~CollisionManager(){ }

void CollisionManager::add3DCollider(Collider3D collider)
{
    m3DColliders.push_back(collider);
}

void CollisionManager::actualizeCollider(Collider3D collider)
{
    for(int i(0); i < m3DColliders.size();i++)
    {
        if(m3DColliders[i].getName() == collider.getName())
        {
            m3DColliders[i] = collider;
        }
    }
}

std::string CollisionManager::checkNearestCollision(glm::vec3 rayStart,glm::vec3 rayEnd)
{
    m3DCollidersHit.clear();
    mNormes.clear();

    for(int i(0); i < m3DColliders.size(); i++)
    {
        if(m3DColliders[i].checkRayCollision(rayStart,rayEnd))
        {
            glm::vec3 vecMax;
            glm::vec3 vecMin;
            if(rayStart.x > rayEnd.x)
            {
                vecMax.x = rayStart.x;
                vecMin.x = rayEnd.x;
            }
            else
            {
                vecMax.x = rayEnd.x;
                vecMin.x = rayStart.x;
            }
            if(rayStart.y > rayEnd.y)
            {
                vecMax.y = rayStart.y;
                vecMin.y = rayEnd.y;
            }
            else
            {
                vecMax.y = rayEnd.y;
                vecMin.y = rayStart.y;
            }
            if(rayStart.z > rayEnd.z)
            {
                vecMax.z = rayStart.z;
                vecMin.z = rayEnd.z;
            }
            else
            {
                vecMax.z = rayEnd.z;
                vecMin.z = rayStart.z;
            }
            glm::vec3 hitPos= m3DColliders[i].getHitRayPosition();

            if(hitPos.x >= vecMin.x && hitPos.x <= vecMax.x && hitPos.y >= vecMin.y && hitPos.y <= vecMax.y &&
               hitPos.z >= vecMin.z && hitPos.z <= vecMax.z)
            {
                m3DCollidersHit.push_back(m3DColliders[i]);
            }
        }
    }

    if(m3DCollidersHit.size() == 0)
    {
        std::string retour = "Pas de collision";
        return retour;
    }
    mNormes.clear();
    for(int i(0); i < m3DCollidersHit.size(); i++)
    {
        glm::vec3 vecteur_depart_collision;
        vecteur_depart_collision = m3DCollidersHit[i].getHitRayPosition()-rayStart;
        float norme = (float) sqrt( vecteur_depart_collision.x*vecteur_depart_collision.x+
                                    vecteur_depart_collision.y*vecteur_depart_collision.y+
                                    vecteur_depart_collision.z*vecteur_depart_collision.z);

        mNormes.push_back(norme);
    }
    float norme;
    for(int i(0); i < mNormes.size(); i++)
    {
        if(i == 0)
        {
            norme = mNormes[0];
        }
        if(mNormes[i] < norme)
        {
            norme = mNormes[i];
        }

    }
    for(int h(0); h < mNormes.size(); h++)
    {
        if(mNormes[h] == norme)
        {
            mLastColliderName = m3DCollidersHit[h].getName();
            return m3DCollidersHit[h].getName();
        }
    }
}

int CollisionManager::getNbCollider() const
{
    return m3DColliders.size();
}

glm::vec3 CollisionManager::getHitPosition()
{
    for(int i(0); i < m3DColliders.size(); i ++)
    {
        if(mLastColliderName == m3DColliders[i].getName())
        {
            return m3DColliders[i].getHitRayPosition();
        }
    }
}
