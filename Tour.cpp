#include "Tour.h"

Tour::Tour(char equipe, char side) : Piece(equipe)
{
    std::string name;
    std::string texture;
    mNbCases = 28;
    mNbEatCases = 28;
    float pos_x;
    float pos_z;

    if(equipe == 'B')
    {
        name = "Blanc_";
        texture = "Piece_Blanc.png";
        pos_z = 7;
    }
    else if(equipe == 'N')
    {
        name = "Noir_";
        texture = "Piece_Noir.png";
        pos_z = -7;
    }
    else
        std::cout << "Equipe invalide" << std::endl;
    if(side == 'G')
    {
        name += "Tour_Gauche";
        pos_x = -7;
    }
    else if(side == 'D')
    {
        name += "Tour_Droite";
        pos_x = 7;
    }

    mMesh = new Mesh(name,1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag",texture,"TourBis.obj");
    mMesh->charger();
    mMesh->setPosition(glm::vec3(pos_x,1.0,pos_z));
    actualiseCases();
    mMesh->addCollider3D(name,"RECT",glm::vec3(1.5,3,1.5),glm::vec3(0,0.75,0));
}

Tour::~Tour() {}

void Tour::actualiseCases()
{
    unsigned int compteur = 0;
    for(int i(0); i < 4; i++)
    {
        for(int j(1); j < 8; j++)
        {
            switch(i)
            {
            case 0:
                mCases[compteur].x = mMesh->getPosition().x;
                mCases[compteur].y = mMesh->getPosition().z+(j*2);
                break;
            case 1:
                mCases[compteur].x = mMesh->getPosition().x;
                mCases[compteur].y = mMesh->getPosition().z-(j*2);
                break;
            case 2:
                mCases[compteur].x = mMesh->getPosition().x+(j*2);
                mCases[compteur].y = mMesh->getPosition().z;
                break;
            case 3:
                mCases[compteur].x = mMesh->getPosition().x-(j*2);
                mCases[compteur].y = mMesh->getPosition().z;
                break;
            }
            mEatCases[compteur].x = mCases[compteur].x;
            mEatCases[compteur].y = mCases[compteur].y;
            compteur ++;
        }
    }
}

void Tour::bloquerCases(CollisionManager *collisionMgr)
{
    mCasesBloquesDeplacement.clear();
    mCasesBloquesEat.clear();

    glm::vec3 meshPos(mMesh->getPosition());
    glm::vec3 vecteurAvantStart(meshPos.x,meshPos.y+1,meshPos.z-1);
    glm::vec3 vecteurAvantEnd(meshPos.x,meshPos.y+1,meshPos.z-14);
    glm::vec3 vecteurArriereStart(meshPos.x,meshPos.y+1,meshPos.z+1);
    glm::vec3 vecteurArriereEnd(meshPos.x,meshPos.y+1,meshPos.z+14);
    glm::vec3 vecteurGaucheStart(meshPos.x-1,meshPos.y+1,meshPos.z);
    glm::vec3 vecteurGaucheEnd(meshPos.x-14,meshPos.y+1,meshPos.z);
    glm::vec3 vecteurDroitStart(meshPos.x+1,meshPos.y+1,meshPos.z);
    glm::vec3 vecteurDroitEnd(meshPos.x+14,meshPos.y+1,meshPos.z);
    memset(mCaseColor,'V',mNbCases);
    if(collisionMgr->checkNearestCollision(vecteurArriereStart,vecteurArriereEnd) != "Pas de collision")
    {
        glm::vec3 collidePos(collisionMgr->getHitPosition());
        bool hit = false;
        for(int i(0); i < 7; i++)
        {
            if(hit)
            {
                mCasesBloquesDeplacement.push_back(i);
                mCasesBloquesEat.push_back(i);
                mCaseColor[i] = 'R';
            }
            else if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1 && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
            {
                hit = true;
                mCasesBloquesDeplacement.push_back(i);
                if(collisionMgr->checkNearestCollision(vecteurArriereStart,vecteurArriereEnd)[0] != mEquipe)
                    mCaseColor[i] = 'Y';
                else
                    mCaseColor[i] = 'R';
            }
        }
    }
    if(collisionMgr->checkNearestCollision(vecteurAvantStart,vecteurAvantEnd) != "Pas de collision")
    {
        glm::vec3 collidePos(collisionMgr->getHitPosition());
        bool hit = false;
        for(int i(7); i < 14; i++)
        {
            if(hit)
            {
                mCasesBloquesDeplacement.push_back(i);
                mCasesBloquesEat.push_back(i);
                mCaseColor[i] = 'R';
            }
            else if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1 && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
            {
                hit = true;
                mCasesBloquesDeplacement.push_back(i);
                if(collisionMgr->checkNearestCollision(vecteurAvantStart,vecteurAvantEnd)[0] != mEquipe)
                    mCaseColor[i] = 'Y';
                else
                    mCaseColor[i] = 'R';
            }
        }
    }
    if(collisionMgr->checkNearestCollision(vecteurDroitStart,vecteurDroitEnd) != "Pas de collision")
    {
        glm::vec3 collidePos(collisionMgr->getHitPosition());
        bool hit = false;
        for(int i(14); i < 21; i++)
        {
            if(hit)
            {
                mCasesBloquesDeplacement.push_back(i);
                mCasesBloquesEat.push_back(i);
                mCaseColor[i] = 'R';
            }else if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1 && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
            {
                hit = true;
                mCasesBloquesDeplacement.push_back(i);
                if(collisionMgr->checkNearestCollision(vecteurDroitStart,vecteurDroitEnd)[0] != mEquipe)
                    mCaseColor[i] = 'Y';
                else
                    mCaseColor[i] = 'R';
            }
        }
    }
    if(collisionMgr->checkNearestCollision(vecteurGaucheStart,vecteurGaucheEnd) != "Pas de collision")
    {
        glm::vec3 collidePos(collisionMgr->getHitPosition());
        bool hit = false;
        for(int i(21); i < 28; i++)
        {
            if(hit)
            {
                mCaseColor[i] = 'R';
                mCasesBloquesDeplacement.push_back(i);
                mCasesBloquesEat.push_back(i);
            }
            else if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1 && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
            {
                hit = true;
                mCasesBloquesDeplacement.push_back(i);
                if(collisionMgr->checkNearestCollision(vecteurGaucheStart,vecteurGaucheEnd)[0] != mEquipe)
                    mCaseColor[i] = 'Y';
                else
                    mCaseColor[i] = 'R';
            }
        }
    }
}
