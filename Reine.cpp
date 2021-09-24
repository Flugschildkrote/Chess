#include "Reine.h"

Reine::Reine(char equipe) : Piece(equipe)
{
    std::string name;
    std::string texture;
    mNbCases = 56;
    mNbEatCases = 56;
    float pos_x = 1;
    float pos_z;

    if(equipe == 'B')
    {
        name = "Blanc_Reine";
        texture = "Piece_Blanc.png";
        pos_z = 7;
    }
    else if(equipe == 'N')
    {
        name = "Noir_Reine";
        texture = "Piece_Noir.png";
        pos_z = -7;
    }
    else
        std::cout << "Equipe invalide" << std::endl;

    mMesh = new Mesh(name,1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag",texture,"Reine.obj");
    mMesh->charger();
    mMesh->setPosition(glm::vec3(pos_x,1.0,pos_z));
    actualiseCases();
    mMesh->addCollider3D(name,"RECT",glm::vec3(1.5,3,1.5),glm::vec3(0,0.75,0));
}

Reine::~Reine() {}

void Reine::actualiseCases()
{
    unsigned int compteur = 0;

    for(int i(0); i < 8; i++)
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
            case 4:
                mCases[compteur].x = mMesh->getPosition().x-(j*2);
                mCases[compteur].y = mMesh->getPosition().z-(j*2);
                break;
            case 5:
                mCases[compteur].x = mMesh->getPosition().x-(j*2);
                mCases[compteur].y = mMesh->getPosition().z+(j*2);
                break;
            case 6:
                mCases[compteur].x = mMesh->getPosition().x+(j*2);
                mCases[compteur].y = mMesh->getPosition().z+(j*2);
                break;
            case 7:
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

void Reine::bloquerCases(CollisionManager *collisionMgr)
{
    mCasesBloquesDeplacement.clear();
    mCasesBloquesEat.clear();

    glm::vec3 vecteurs[8][2];
    glm::vec3 meshPos(mMesh->getPosition());

    vecteurs[0][0] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z+1); //Case Arriere
    vecteurs[0][1] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z+14);
    vecteurs[1][0] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z-1); //Case Avant
    vecteurs[1][1] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z-14);
    vecteurs[2][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z); //Case Droite
    vecteurs[2][1] = glm::vec3(meshPos.x+14,meshPos.y+1,meshPos.z);
    vecteurs[3][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z); //Case Gauche
    vecteurs[3][1] = glm::vec3(meshPos.x-14,meshPos.y+1,meshPos.z);
    vecteurs[4][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z-1); //Case Avant gauche
    vecteurs[4][1] = glm::vec3(meshPos.x-14,meshPos.y+1,meshPos.z-14);
    vecteurs[5][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z+1); //Case Arriere Gauche
    vecteurs[5][1] = glm::vec3(meshPos.x-14,meshPos.y+1,meshPos.z+14);
    vecteurs[6][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z+1); //Case Arriere Droite
    vecteurs[6][1] = glm::vec3(meshPos.x+14,meshPos.y+1,meshPos.z+14);
    vecteurs[7][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z-1); //Case Avant Droite
    vecteurs[7][1] = glm::vec3(meshPos.x+14,meshPos.y+1,meshPos.z-14);

    memset(mCaseColor,'V', mNbCases);
    for(int j(0); j < 8; j++)
    {
        if(collisionMgr->checkNearestCollision(vecteurs[j][0],vecteurs[j][1]) != "Pas de collision")
        {
            glm::vec3 collidePos(collisionMgr->getHitPosition());
            bool hit = false;
            int i = j*7;
            int valMax = i+7;
            for(i; i < valMax; i++)
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
