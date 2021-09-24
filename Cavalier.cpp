#include "Cavalier.h"

Cavalier::Cavalier(char equipe, char side) : Piece(equipe)
{
    std::string name;
    std::string texture;
    mNbCases = 8;
    mNbEatCases = 8;
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
        name += "Cavalier_Gauche";
        pos_x = -5;
    }
    else if(side == 'D')
    {
        name += "Cavalier_Droite";
        pos_x = 5;
    }

    mMesh = new Mesh(name,1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag",texture,"Cavalier.obj");
    mMesh->charger();
    mMesh->setPosition(glm::vec3(pos_x,1.0,pos_z));
    actualiseCases();
    mMesh->addCollider3D(name,"RECT",glm::vec3(1.5,3,1.5),glm::vec3(0,0.75,0));
}

Cavalier::~Cavalier(){ }

void Cavalier::actualiseCases()
{
    mCases[0].x = mMesh->getPosition().x-4;
    mCases[0].y = mMesh->getPosition().z-2;

    mCases[1].x = mMesh->getPosition().x-4;
    mCases[1].y = mMesh->getPosition().z+2;

    mCases[2].x = mMesh->getPosition().x+4;
    mCases[2].y = mMesh->getPosition().z+2;

    mCases[3].x = mMesh->getPosition().x+4;
    mCases[3].y = mMesh->getPosition().z-2;

    mCases[4].x = mMesh->getPosition().x-2;
    mCases[4].y = mMesh->getPosition().z-4;

    mCases[5].x = mMesh->getPosition().x-2;
    mCases[5].y = mMesh->getPosition().z+4;

    mCases[6].x = mMesh->getPosition().x+2;
    mCases[6].y = mMesh->getPosition().z+4;

    mCases[7].x = mMesh->getPosition().x+2;
    mCases[7].y = mMesh->getPosition().z-4;

    for(int i(0); i < 8; i++)
    {
        mEatCases[i].x = mCases[i].x;
        mEatCases[i].y = mCases[i].y;
    }
}

void Cavalier::bloquerCases(CollisionManager *collisionMgr)
{
    mCasesBloquesDeplacement.clear();
    mCasesBloquesEat.clear();

    glm::vec3 meshPos(mMesh->getPosition());
    glm::vec3 vecteurs[8][2];
    vecteurs[0][0] = glm::vec3(meshPos.x-4,meshPos.y+1,meshPos.z-1);
    vecteurs[0][1] = glm::vec3(meshPos.x-4,meshPos.y+1,meshPos.z-3);
    vecteurs[1][0] = glm::vec3(meshPos.x-4,meshPos.y+1,meshPos.z+1);
    vecteurs[1][1] = glm::vec3(meshPos.x-4,meshPos.y+1,meshPos.z+3);
    vecteurs[2][0] = glm::vec3(meshPos.x+4,meshPos.y+1,meshPos.z+1);
    vecteurs[2][1] = glm::vec3(meshPos.x+4,meshPos.y+1,meshPos.z+3);
    vecteurs[3][0] = glm::vec3(meshPos.x+4,meshPos.y+1,meshPos.z-1);
    vecteurs[3][1] = glm::vec3(meshPos.x+4,meshPos.y+1,meshPos.z-3);
    vecteurs[4][0] = glm::vec3(meshPos.x-2,meshPos.y+1,meshPos.z-3);
    vecteurs[4][1] = glm::vec3(meshPos.x-2,meshPos.y+1,meshPos.z-5);
    vecteurs[5][0] = glm::vec3(meshPos.x-2,meshPos.y+1,meshPos.z+3);
    vecteurs[5][1] = glm::vec3(meshPos.x-2,meshPos.y+1,meshPos.z+5);
    vecteurs[6][0] = glm::vec3(meshPos.x+2,meshPos.y+1,meshPos.z+3);
    vecteurs[6][1] = glm::vec3(meshPos.x+2,meshPos.y+1,meshPos.z+5);
    vecteurs[7][0] = glm::vec3(meshPos.x+2,meshPos.y+1,meshPos.z-3);
    vecteurs[7][1] = glm::vec3(meshPos.x+2,meshPos.y+1,meshPos.z-5);

    memset(mCaseColor, 'V', mNbCases);
    for(int i(0); i < 8; i++)
    {
        if(collisionMgr->checkNearestCollision(vecteurs[i][0],vecteurs[i][1]) != "Pas de collision")
        {
            glm::vec3 collidePos(collisionMgr->getHitPosition());
            if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1 && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
            {
                if(collisionMgr->checkNearestCollision(vecteurs[i][0],vecteurs[i][1])[0] != mEquipe)
                    mCaseColor[i] = 'Y';
                else
                    mCaseColor[i] = 'R';
                mCasesBloquesDeplacement.push_back(i);
            }
        }
    }
}
