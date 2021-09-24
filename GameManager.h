#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "Terrain.h"
#include "Pion.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Reine.h"
#include "Roi.h"
#include "Piece.h"

#include "CollisionManager.h"
#include "GUI_Manager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void actualizeAllColliders(bool actualizeCases);
    void drawScene(const glm::mat4 projection,const glm::mat4 view);
    void play(const bool mouseButton1,const glm::vec3 mouse_x,const glm::vec3 mouse_y);
    bool checkSafe(Piece *piece);
    void passerTour();
private:
    Terrain *mTerrain;
    GUI_Manager mGUI;
    Piece *mPieces[2][16];
    Mesh mCaseVerte;
    Mesh mCaseJaune;
    Mesh mCaseRouge;
    glm::vec3 vecteur;
    glm::vec3 vecteur2;
    int mNbPiecesBlanchesMortes;
    int mNbPiecesNoiresMortes;
    CollisionManager *mCollisionMgr;
    CollisionManager *mCollisionMgr2;
    int mLastPieceID;
    int mLastPieceTeam;
    int mActivePieceTeam;
    int mActivePieceID;
    bool isPieceActive;
    bool mousePressed;
    char mTurn;
};

#endif // GAMEMANAGER_H_INCLUDED
