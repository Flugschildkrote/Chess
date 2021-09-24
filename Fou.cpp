#include "Fou.h"

Fou::Fou(char equipe, char side) : Piece(equipe)
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
        name += "Fou_Gauche";
        pos_x = -3;
    }
    else if(side == 'D')
    {
        name += "Fou_Droite";
        pos_x = 3;
    }

    mMesh = new Mesh(name,1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag",texture,"Fou.obj");
    mMesh->charger();
    mMesh->setPosition(glm::vec3(pos_x,1.0,pos_z));
    actualiseCases();
    mMesh->addCollider3D(name,"RECT",glm::vec3(1.5,3,1.5),glm::vec3(0,0.75,0));
}

Fou::~Fou() {}

void Fou::actualiseCases()
{
    unsigned int compteur = 0;

    for(int i(0); i < 4; i++)
    {
        for(int j(1); j < 8; j++)
        {
            switch(i)
            {
            case 0:
                mCases[compteur].x = mMesh->getPosition().x-(j*2);
                mCases[compteur].y = mMesh->getPosition().z-(j*2);
                break;
            case 1:
                mCases[compteur].x = mMesh->getPosition().x-(j*2);
                mCases[compteur].y = mMesh->getPosition().z+(j*2);
                break;
            case 2:
                mCases[compteur].x = mMesh->getPosition().x+(j*2);
                mCases[compteur].y = mMesh->getPosition().z+(j*2);
                break;
            case 3:
                mCases[compteur].x = mMesh->getPosition().x+(j*2);
                mCases[compteur].y = mMesh->getPosition().z-(j*2);
                break;
            }
            mEatCases[compteur].x = mCases[compteur].x;
            mEatCases[compteur].y = mCases[compteur].y;
            compteur ++;
        }
    }
}

void Fou::bloquerCases(CollisionManager *collisionMgr)
{
    mCasesBloquesDeplacement.clear();
    mCasesBloquesEat.clear();

    glm::vec3 vecteurs[4][2];
    glm::vec3 meshPos(mMesh->getPosition());

    vecteurs[0][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z-1); //Case Avant gauche
    vecteurs[0][1] = glm::vec3(meshPos.x-14,meshPos.y+1,meshPos.z-14);
    vecteurs[1][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z+1); //Case Arriere Gauche
    vecteurs[1][1] = glm::vec3(meshPos.x-14,meshPos.y+1,meshPos.z+14);
    vecteurs[2][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z+1); //Case Arriere Droite
    vecteurs[2][1] = glm::vec3(meshPos.x+14,meshPos.y+1,meshPos.z+14);
    vecteurs[3][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z-1); //Case Avant Droite
    vecteurs[3][1] = glm::vec3(meshPos.x+14,meshPos.y+1,meshPos.z-14);
    memset(mCaseColor, 'V', mNbCases);
    for(int j(0); j < 4; j++)
    {
        if(collisionMgr->checkNearestCollision(vecteurs[j][0],vecteurs[j][1]) != "Pas de collision")
        {
            glm::vec3 collidePos(collisionMgr->getHitPosition());
            bool hit = false;
            int i = j*7;
            int valMax = i+7;
            for(i ;  i < valMax; i++)
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
                    if(collisionMgr->checkNearestCollision(vecteurs[j][0],vecteurs[j][1])[0] != mEquipe)
                        mCaseColor[i] = 'Y';
                    else
                       mCaseColor[i] = 'R';
                }
            }
        }
    }
}
