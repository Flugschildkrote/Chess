#include "GameManager.h"

GameManager::GameManager() : mTurn('B'), mLastPieceID(0), mLastPieceTeam(0), isPieceActive(false), mNbPiecesBlanchesMortes(0), mNbPiecesNoiresMortes(0), vecteur(-1,2,1), vecteur2(-1,2,9), mGUI(),
                            mCaseVerte("CaseVerte",0.8,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag","Piece_Vert.png","Cube1.obj"),
                            mCaseJaune("CaseJaune",0.8,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag","Piece_Jaune.png","Cube1.obj"),
                            mCaseRouge("CaseRouge",0.8,"Shaders/diffuseLight.vert","Shaders/diffuseLight.frag","Piece_Rouge.png","Cube1.obj")
{
    char team;
    mCaseVerte.scale(glm::vec3(0.8,0.2,0.8));
    mCaseJaune.scale(glm::vec3(0.8,0.2,0.8));
    mCaseRouge.scale(glm::vec3(0.8,0.2,0.8));
    mCaseVerte.charger();
    mCaseJaune.charger();
    mCaseRouge.charger();
    mGUI.addText("Tour : Blancs", glm::vec3(-1,1,0),glm::vec3(0,0.8,0));
    mGUI.addText("Tour : noirs", glm::vec3(-1,1,0),glm::vec3(-0.08,0.8,0));
    mGUI.addText("Echec roi blanc", glm::vec3(-1,-0.9,0),glm::vec3(-0.7,-1,0));
    mGUI.addText("Echec roi noir", glm::vec3(0.7,-0.9,0),glm::vec3(1,-1,0));
    mGUI.hideText("Echec roi blanc",true);
    mGUI.hideText("Echec roi noir",true);
    mCollisionMgr = new CollisionManager;
    mCollisionMgr2 = new CollisionManager;
    mTerrain = new Terrain();
    std::cout << "Terrain Loaded" << std::endl;

    for(int  i(0); i < 5; i++)
    {
        mCollisionMgr->add3DCollider(mTerrain->getCollider(i));
        mCollisionMgr2->add3DCollider(mTerrain->getCollider(i));
    }

    for(int h(0); h < 2; h++)
    {
        if(h == 0)
            team = 'B';
        else
            team = 'N';

        for(int i(0); i < 8; i++)
        {
            mPieces[h][i] = new Pion(team,i); std::cout << mPieces[h][i]->getName() << " Loaded" << std::endl;
        }

        mPieces[h][8] = new Tour(team,'G');  std::cout << mPieces[h][8]->getName() << " Loaded" << std::endl;
        mPieces[h][9] = new Tour(team,'D');  std::cout << mPieces[h][9]->getName() << " Loaded" << std::endl;
        mPieces[h][10] = new Cavalier(team,'G'); std::cout << mPieces[h][10]->getName() << " Loaded" << std::endl;
        mPieces[h][11] = new Cavalier(team,'D'); std::cout << mPieces[h][11]->getName() << " Loaded" << std::endl;
        mPieces[h][12] = new Fou(team,'G'); std::cout << mPieces[h][12]->getName() << " Loaded" << std::endl;
        mPieces[h][13] = new Fou(team,'D'); std::cout << mPieces[h][13]->getName() << " Loaded" << std::endl;
        mPieces[h][14] = new Reine(team); std::cout << mPieces[h][14]->getName() << " Loaded" << std::endl;
        mPieces[h][15] = new Roi(team); std::cout << mPieces[h][15]->getName() << " Loaded" << std::endl;
    }

    for(int h(0); h < 2; h++)
    {
        for(int i(0); i < 16; i++)
        {
            mCollisionMgr->add3DCollider(mPieces[h][i]->getCollider(0));
            mCollisionMgr2->add3DCollider(mPieces[h][i]->getCollider(0));
        }
    }

    for(int h(0); h < 2; h++)
    {
        for(int i(0); i < 16; i++)
        {
            mPieces[h][i]->bloquerCases(mCollisionMgr2);
        }
    }
}

GameManager::~GameManager()
{
    delete mTerrain;
    delete mCollisionMgr;
    delete mCollisionMgr2;

    for(int h(0); h < 2; h++)
    {
        for(int i(0); i < 16; i++)
        {
            delete mPieces[h][i];
        }
    }
}

void GameManager::actualizeAllColliders(bool actualizeCases)
{
    for(int i(0); i < 5; i++)
    {
        mCollisionMgr->actualizeCollider(mTerrain->getCollider(i));
        mCollisionMgr2->actualizeCollider(mTerrain->getCollider(i));
    }

    for(int h(0); h < 2; h++)
    {
        for(int i(0); i < 16; i++)
        {
            mCollisionMgr->actualizeCollider(mPieces[h][i]->getCollider(0));
            mCollisionMgr2->actualizeCollider(mPieces[h][i]->getCollider(0));
        }
    }
    if(actualizeCases)
    {
        for(int h(0); h < 2; h++)
        {
            for(int i(0); i < 16; i++)
            {
                mPieces[h][i]->bloquerCases(mCollisionMgr2);
            }
        }
    }
}

void GameManager::drawScene(const glm::mat4 projection, const glm::mat4 view)
{
    mTerrain->afficher(projection,view);

    for(int h(0); h < 2; h++)
    {
        for(int i(0); i < 16; i++)
        {
            mPieces[h][i]->afficher(projection, view, mCaseVerte,mCaseJaune,mCaseRouge);
        }
    }
    mGUI.afficher();
}

void GameManager::play(const bool mouseButton1, glm::vec3 mouse_x, glm::vec3 mouse_y)
{
    actualizeAllColliders(false);

    std::string colliderResult = mCollisionMgr->checkNearestCollision(mouse_x,mouse_y);
    std::cout << colliderResult << std::endl;
    if(mouseButton1)
    {
        if(!mousePressed)
        {
            int h;
            int hBarre;
            if(mTurn == 'B')
            {
                h = 0;
                hBarre = 1;
            }
            else
            {
                h = 1;
                hBarre = 0;
            }

            if(colliderResult == mPieces[mLastPieceTeam][mLastPieceID]->getName() && mLastPieceTeam == h)
            {
                if(!mPieces[mLastPieceTeam][mLastPieceID]->getState())
                {
                    if(isPieceActive)
                        mPieces[mActivePieceTeam][mActivePieceID]->setActive(false);
                    std::cout << "OK" << std::endl;
                    mPieces[mLastPieceTeam][mLastPieceID]->setActive(true);
                    mPieces[mLastPieceTeam][mLastPieceID]->setIntensity(0.5);
                    mActivePieceTeam = mLastPieceTeam;
                    mActivePieceID = mLastPieceID;
                    isPieceActive = true;
                }
                else
                {
                    mPieces[mLastPieceTeam][mLastPieceID]->setActive(false);
                    isPieceActive = false;
                }
            }
            else if(colliderResult == mTerrain->getCollider(0).getName() && isPieceActive)
            {
                if(mPieces[mActivePieceTeam][mActivePieceID]->getState())
                {
                    glm::vec3 posPieceActuelle = glm::vec3(mPieces[mActivePieceTeam][mActivePieceID]->getPosition());
                    if(mPieces[mActivePieceTeam][mActivePieceID]->checkMove(mCollisionMgr->getHitPosition()))
                    {
                        mPieces[mActivePieceTeam][mActivePieceID]->setActive(false);
                        mPieces[mActivePieceTeam][mActivePieceID]->setIntensity(0.8);
                        isPieceActive = false;

                        actualizeAllColliders(true);

                        if(checkSafe(mPieces[mActivePieceTeam][15]))
                        {
                            passerTour();
                        }
                        else
                        {
                            std::cout << "DANGER" << std::endl;
                            mPieces[mActivePieceTeam][mActivePieceID]->setPosition(posPieceActuelle);
                            actualizeAllColliders(true);
                        }
                    }
                    else
                    {
                        mPieces[mActivePieceTeam][mActivePieceID]->setActive(false);
                        mPieces[mActivePieceTeam][mActivePieceID]->setIntensity(0.8);
                        isPieceActive = false;
                    }
                }
            }
            else
            {
                for(int i(0); i < 16; i++)
                {
                    if(i != 15)
                    {
                        if(colliderResult == mPieces[hBarre][i]->getName() && mPieces[hBarre][i]->getLifeState() && isPieceActive)
                        {
                            glm::vec3 clickedPiecesPos = mPieces[hBarre][i]->getPosition();
                            glm::vec3 acvivPiecePos = mPieces[mActivePieceTeam][mActivePieceID]->getPosition();
                            if(mPieces[mActivePieceTeam][mActivePieceID]->checkEat(clickedPiecesPos,true))
                            {
                                mPieces[mActivePieceTeam][mActivePieceID]->setActive(false);
                                mPieces[mActivePieceTeam][mActivePieceID]->setIntensity(0.8);
                                isPieceActive = false;
                                mPieces[hBarre][i]->setPosition(glm::vec3(-10,-10,-10));
                                actualizeAllColliders(true);

                                if(checkSafe(mPieces[mActivePieceTeam][15]))
                                {
                                    mPieces[hBarre][i]->setAlive(false);
                                    int x = 0;
                                    if(hBarre == 0)
                                    {
                                        if(mNbPiecesBlanchesMortes >= 8)
                                            x = 2;
                                        mPieces[hBarre][i]->setPosition(glm::vec3(10+x,1.5,-7+2*mNbPiecesBlanchesMortes-(7*x+(1*x/2))));
                                        mNbPiecesBlanchesMortes ++;
                                    }
                                    else
                                    {
                                        if(mNbPiecesNoiresMortes >= 8)
                                            x = 2;
                                        mPieces[hBarre][i]->setPosition(glm::vec3(-10-x,1.5,7-2*mNbPiecesNoiresMortes+(7*x+(1*x/2))));
                                        mNbPiecesNoiresMortes ++;
                                    }
                                    passerTour();
                                }
                                else
                                {
                                    std::cout << "DANGER" << std::endl;
                                    mPieces[hBarre][i]->setPosition(clickedPiecesPos);
                                    mPieces[mActivePieceTeam][mActivePieceID]->setPosition(acvivPiecePos);
                                }
                            }
                            else
                            {
                                mPieces[mActivePieceTeam][mActivePieceID]->setActive(false);
                                mPieces[mActivePieceTeam][mActivePieceID]->setIntensity(0.8);
                                mPieces[hBarre][i]->setIntensity(0.8);
                                isPieceActive = false;
                            }
                        }
                    }
                }
            }
        }
        mousePressed = true;
    }
    else
    {
        mousePressed = false;
        int h;
        int hBarre;
        if(mTurn == 'B')
        {
            h = 0;
            hBarre = 1;
            mGUI.hideText("Tour : Blancs",false);
            mGUI.hideText("Tour : noirs",true);
        }
        else
        {
            h = 1;
            hBarre = 0;
            mGUI.hideText("Tour : Blancs",true);
            mGUI.hideText("Tour : noirs",false);
        }
            for(int i(0); i < 16; i++)
            {
                if(colliderResult == mPieces[h][i]->getName() && mPieces[h][i]->getLifeState())
                {
                    if(!mPieces[h][i]->getState())
                        mPieces[h][i]->setIntensity(0.6);
                    else
                        mPieces[h][i]->setIntensity(0.35);
                    mLastPieceID = i;
                    mLastPieceTeam = h;
                }else
                {
                    if(!mPieces[h][i]->getState())
                        mPieces[h][i]->setIntensity(0.8);
                    else
                        mPieces[h][i]->setIntensity(0.5);
                }

                if(isPieceActive)
                {
                    if(i != 15) /*On exclu le roi */
                    {
                        if(colliderResult == mPieces[hBarre][i]->getName() && mPieces[hBarre][i]->getLifeState())
                        {
                            mPieces[hBarre][i]->setIntensity(0.6);
                            mLastPieceID = i;
                            mLastPieceTeam = h;
                        }else if(mPieces[hBarre][i]->getLifeState())
                        {
                            mPieces[hBarre][i]->setIntensity(0.8);
                        }
                    }
                }
            }
    }
}

bool GameManager::checkSafe(Piece *piece)
{
    int equipeAdverse;
    glm::vec3 pos = glm::vec3(piece->getPosition());
    if(piece->getTeam() == 'B')
        equipeAdverse = 1;
    else
        equipeAdverse = 0;

    std::cout << equipeAdverse << std::endl;
    for(int i(0); i < 16; i++)
    {
        if(mPieces[equipeAdverse][i]->checkEat(pos,false))
        {
            if(equipeAdverse == 0)
            {
                mGUI.hideText("Echec roi noir",false);
            }
            else
            {
                mGUI.hideText("Echec roi blanc",false);
            }
            //mPieces[equipeAdverse][i]->setTexture("Piece_Rouge.png");
            return false;
        }
    }
    mGUI.hideText("Echec roi blanc",true);
    mGUI.hideText("Echec roi noir",true);
    return true;
}
void GameManager::passerTour()
{
    if(mTurn == 'N')
        mTurn = 'B';
    else
        mTurn = 'N';

    if(mTurn == 'B')
        checkSafe(mPieces[0][15]);
    else
        checkSafe(mPieces[0][15]);

    mPieces[mLastPieceTeam][mLastPieceID]->setIntensity(0.8);
}
