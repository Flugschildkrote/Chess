#include "Pion.h"

Pion::Pion()
{

}

Pion::Pion(char equipe, char number) : Piece(equipe)//mEquipe(equipe), isActive(false)
{
    std::string name;
    std::string texture;
    mNbCases = 2;
    mNbEatCases = 2;
    float pos_x = (2*number)-7;
    float pos_z;
    float z;

    if(equipe == 'B')
    {
        name = "Blanc_Pion_";
        texture = "Piece_Blanc.png";
        pos_z = 5;
        z = -1;
    }
    else if(equipe == 'N')
    {
        name = "Noir_Pion_";
        texture = "Piece_Noir.png";
        pos_z = -5;
        z = 1;
    }
    else
        std::cout << "Equipe invalide" << std::endl;

    switch(number)
    {
    case 0:
        name += "1";
        break;
    case 1:
        name += "2";
        break;
    case 2:
        name += "3";
        break;
    case 3:
        name += "4";
        break;
    case 4:
        name += "5";
        break;
    case 5:
        name += "6";
        break;
    case 6:
        name += "7";
        break;
    case 7:
        name += "8";
        break;
    case 10:
        name += "10";
    }

    mMesh = new Mesh(name,1.0,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag",texture,"Pion.obj");
    mMesh->charger();
    mMesh->setPosition(glm::vec3(pos_x,1.0,pos_z));
    mCases[0].y = mMesh->getPosition().z+(2*z);
    actualiseCases();
    mMesh->addCollider3D(name,"RECT",glm::vec3(1.5,3,1.5),glm::vec3(0,0.75,0));
}

Pion::~Pion()
{

}

void Pion::actualiseCases()
{
    int z;
    if(mEquipe == 'B')
        z = -1;
    else
        z = 1;

    float caseY = mCases[0].y;
    mCases[0].x = mMesh->getPosition().x;
    mCases[0].y = mMesh->getPosition().z+(2*z);

    if(caseY != mCases[0].y)
        mNbCases = 1;

    mCases[1].x = mMesh->getPosition().x;
    mCases[1].y = mMesh->getPosition().z+(2*2*z);

    mEatCases[0].x = mMesh->getPosition().x+2;
    mEatCases[0].y = mMesh->getPosition().z+(2*z);

    mEatCases[1].x = mMesh->getPosition().x-2;
    mEatCases[1].y = mMesh->getPosition().z+(2*z);

}

void Pion::bloquerCases(CollisionManager *collisionMgr)
{
    mCasesBloquesDeplacement.clear();
    mCasesBloquesEat.clear();
    int z;
    if(mEquipe == 'B')
        z = -1;
    else
        z = 1;

    glm::vec3 vecteurAvantStart(mMesh->getPosition().x, mMesh->getPosition().y+1, mMesh->getPosition().z+z);
    glm::vec3 vecteurAvantEnd(mMesh->getPosition().x, mMesh->getPosition().y+1, mMesh->getPosition().z+(z*4));
    memset(mCaseColor, 'V', mNbCases);
    if(collisionMgr->checkNearestCollision(vecteurAvantStart,vecteurAvantEnd) != "Pas de collision")
    {
        glm::vec3 collidePos(collisionMgr->getHitPosition());
        bool hit = false;
        for(int i(0); i < 2; i++)
        {
            if(hit)
            {
                mCasesBloquesDeplacement.push_back(i);
                mCaseColor[i] = 'R';
            }
            else if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1 && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
            {
                hit = true;
                mCasesBloquesDeplacement.push_back(i);
                mCaseColor[i] = 'R';
            }
        }
    }
}
