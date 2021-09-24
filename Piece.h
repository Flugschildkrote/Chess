#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "StaticMesh.h"
#include "CollisionManager.h"

class Piece
{
public:
    Piece();
    Piece(char equipe);
    Piece(const Piece &pieceACopier);
    virtual ~Piece();

    Piece& operator=(const Piece &pieceACopier);
    void setPosition(const glm::vec3 newPosition);
    void translate(const glm::vec3 translation);
    void rotate(const float angle, const glm::vec3 axe);
    void scale(const glm::vec3 scale);

    void afficher(glm::mat4 projection, glm::mat4 view,Mesh &caseVerte, Mesh &caseJaune, Mesh &caseRouge);

    Collider3D getCollider(const int id) const;
    std::string getName() const;
    bool getState() const;
    bool getLifeState() const;
    glm::vec3 getPosition() const;

    virtual void actualiseCases();
    bool checkMove( const glm::vec3 collidePos);
    bool checkEat(const glm::vec3 eatPiecePos, bool canEat);
    void setActive(const bool state);
    void setIntensity(const float intensity);
    void setAlive(bool state);
    void setTexture(const std::string newTexture);
    virtual void bloquerCases(CollisionManager *collisionMgr);
    bool checkValidCases(const std::vector<int> &casesInterdites,const int caseAVerifier);
    char getTeam() const;
protected:
    Mesh *mMesh;
    char mEquipe;
    bool isActive;
    bool isAlive;
    int mNbCases;
    int mNbEatCases;
    bool asMoved;
    glm::vec2 mCases[56];
    glm::vec2 mEatCases[56];
    char mCaseColor[56];
    std::vector<int> mCasesBloquesDeplacement;
    std::vector<int> mCasesBloquesEat;
};

#endif // PIECE_H_INCLUDED
