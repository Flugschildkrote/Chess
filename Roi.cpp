#include "Roi.h"

Roi::Roi(char equipe) : Piece(equipe)
{
    std::string name;
    std::string texture;
    mNbCases = 8;
    mNbEatCases = 8;
    float pos_x = -1;
    float pos_z;

    if(equipe == 'B')
    {
        name = "Blanc_Roi";
        texture = "Piece_Blanc.png";
        pos_z = 7;
    }
    else if(equipe == 'N')
    {
        name = "Noir_Roi";
        texture = "Piece_Noir.png";
        pos_z = -7;
    }
    else
        std::cout << "Equipe invalide" << std::endl;

    mMesh = new Mesh(name,1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag",texture,"Roi.obj");
    mMesh->charger();
    mMesh->setPosition(glm::vec3(pos_x,1.0,pos_z));
    actualiseCases();
    mMesh->addCollider3D(name,"RECT",glm::vec3(1.5,3,1.5),glm::vec3(0,0.75,0));
}

Roi::~Roi() {}

void Roi::actualiseCases()
{
    mCases[0].x = mMesh->getPosition().x;
    mCases[0].y = mMesh->getPosition().z-2;

    mCases[1].x = mMesh->getPosition().x+2;
    mCases[1].y = mMesh->getPosition().z-2;

    mCases[2].x = mMesh->getPosition().x+2;
    mCases[2].y = mMesh->getPosition().z;

    mCases[3].x = mMesh->getPosition().x+2;
    mCases[3].y = mMesh->getPosition().z+2;

    mCases[4].x = mMesh->getPosition().x;
    mCases[4].y = mMesh->getPosition().z+2;

    mCases[5].x = mMesh->getPosition().x-2;
    mCases[5].y = mMesh->getPosition().z+2;

    mCases[6].x = mMesh->getPosition().x-2;
    mCases[6].y = mMesh->getPosition().z;

    mCases[7].x = mMesh->getPosition().x-2;
    mCases[7].y = mMesh->getPosition().z-2;

    for(int i(0); i < 8; i++)
    {
        mEatCases[i].x = mCases[i].x;
        mEatCases[i].y = mCases[i].y;
    }
}

void Roi::bloquerCases(CollisionManager *collisionMgr)
{
    mCasesBloquesDeplacement.clear();
    mCasesBloquesEat.clear();

    glm::vec3 vecteurs[8][2];
    glm::vec3 meshPos(mMesh->getPosition());
    vecteurs[0][0] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z-1); //Case Avant
    vecteurs[0][1] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z-3);
    vecteurs[1][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z-1); //Case Avant Droite
    vecteurs[1][1] = glm::vec3(meshPos.x+3,meshPos.y+1,meshPos.z-3);
    vecteurs[2][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z); //Case Droite
    vecteurs[2][1] = glm::vec3(meshPos.x+3,meshPos.y+1,meshPos.z);
    vecteurs[3][0] = glm::vec3(meshPos.x+1,meshPos.y+1,meshPos.z+1); //Case Arriere Droite
    vecteurs[3][1] = glm::vec3(meshPos.x+3,meshPos.y+1,meshPos.z+3);
    vecteurs[4][0] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z+1); //Case Arriere
    vecteurs[4][1] = glm::vec3(meshPos.x,meshPos.y+1,meshPos.z+3);
    vecteurs[5][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z+1); //Case Arriere Gauche
    vecteurs[5][1] = glm::vec3(meshPos.x-3,meshPos.y+1,meshPos.z+3);
    vecteurs[6][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z); //Case Gauche
    vecteurs[6][1] = glm::vec3(meshPos.x-3,meshPos.y+1,meshPos.z);
    vecteurs[7][0] = glm::vec3(meshPos.x-1,meshPos.y+1,meshPos.z-1); //Case Avant gauche
    vecteurs[7][1] = glm::vec3(meshPos.x-3,meshPos.y+1,meshPos.z-3);

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
