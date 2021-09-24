#include "Piece.h"

Piece::Piece()
{

}

Piece::Piece(char equipe) : mEquipe(equipe), isActive(false),isAlive(true),asMoved(false), mNbCases(0), mNbEatCases(0)
{

}

Piece::Piece(const Piece &pieceACopier) : mEquipe(pieceACopier.mEquipe), isActive(pieceACopier.isActive),isAlive(pieceACopier.isAlive),asMoved(pieceACopier.asMoved), mNbCases(pieceACopier.mNbCases), mNbEatCases(pieceACopier.mNbEatCases)
{
    for(int i(0); i < mNbCases; i++)
    {
        mCases[i] = pieceACopier.mCases[i];
        mCaseColor[i] = pieceACopier.mCaseColor[i];
    }

    for(int i(0); i < mNbEatCases; i++)
        mEatCases[i] = pieceACopier.mEatCases[i];

    mMesh = new Mesh(*(pieceACopier.mMesh));
    mMesh->charger();
}

Piece& Piece::operator=(Piece const &pieceACopier)
{
    mEquipe = pieceACopier.mEquipe;
    isActive = pieceACopier.isActive;
    isAlive = pieceACopier.isAlive;
    asMoved = pieceACopier.asMoved;
    mNbCases = pieceACopier.mNbCases;
    mNbEatCases = pieceACopier.mNbEatCases;

    for(int i(0); i < mNbCases; i++)
        mCases[i] = pieceACopier.mCases[0];

    for(int i(0); i < mNbEatCases; i++)
        mEatCases[i] = pieceACopier.mEatCases[0];

    delete mMesh;
    mMesh = new Mesh(*(pieceACopier.mMesh));

    return *this;
}

Piece::~Piece()
{
    std::cout << "[DELETE PIECE]" << std::endl;
    delete mMesh;
}

void Piece::setPosition(const glm::vec3 newPosition)
{
    mMesh->setPosition(newPosition);
    mMesh->actualizeColliderPosition(0);
    actualiseCases();
}

void Piece::translate(const glm::vec3 translation)
{
    mMesh->translate(translation);
    mMesh->actualizeColliderPosition(0);
    actualiseCases();
}

void Piece::rotate(const float angle, const glm::vec3 axe)
{
    mMesh->rotate(angle,axe);
}

void Piece::scale(const glm::vec3 scale)
{
    mMesh->scale(scale);
}

void Piece::afficher(glm::mat4 projection, glm::mat4 view, Mesh &caseVerte, Mesh &caseJaune, Mesh &caseRouge)
{
    mMesh->afficher(projection, view);
    if(isActive)
    {
        int v = 0;
        for(int i(0); i < mNbCases; i++)
        {
            if(mCases[i].x > -8 && mCases[i].x < 8 && mCases[i].y > -8 && mCases[i].y < 8)
            {
                //verifier la case qui n'existe pas dans mdeplacement mais qui existe dans m eat
                if(mCaseColor[i] == 'V')
                {
                    caseVerte.setPosition(glm::vec3(mCases[i].x,1,mCases[i].y));
                    caseVerte.afficher(projection,view);
                }
                else if(mCaseColor[i] == 'Y')
                {
                    caseJaune.setPosition(glm::vec3(mCases[i].x,1,mCases[i].y));
                    caseJaune.afficher(projection,view);
                }
                else if(mCaseColor[i] == 'R')
                {
                    caseRouge.setPosition(glm::vec3(mCases[i].x,1,mCases[i].y));
                    caseRouge.afficher(projection,view);
                }
                else
                {
                    std::cout << "ERROR CASE : " << i << std::endl;
                }
            }
        }
    }
}

Collider3D Piece::getCollider(const int id) const
{
    return mMesh->getCollider(id);
}

std::string Piece::getName() const
{
    return mMesh->getName();
}

bool Piece::getState() const
{
    return isActive;
}

bool Piece::getLifeState() const
{
    return isAlive;
}

glm::vec3 Piece::getPosition() const
{
    return mMesh->getPosition();
}

void Piece::actualiseCases()
{
    std::cout << "No Case to actualize" << std::endl;
}

bool Piece::checkMove(const glm::vec3 collidePos)
{
    for(int i(0); i < mNbCases; i++)
    {
        if(collidePos.x >= mCases[i].x-1 && collidePos.x <= mCases[i].x+1
        && collidePos.z >= mCases[i].y-1 && collidePos.z <= mCases[i].y+1)
        {
                /* std::cout << "Collision : [" << collidePos.x << "; " << collidePos.y << "; " << collidePos.z << "]" << std::endl;
            std::cout << "[" << mCases[i].x << "; " << mMesh->getPosition().y << "; " << mCases[i].y << "]" << std::endl;*/
            if(checkValidCases(mCasesBloquesDeplacement,i))
            {
                glm::vec3 newPos = glm::vec3(mCases[i].x,mMesh->getPosition().y,mCases[i].y);
                setPosition(newPos);
                return true;
            }
        }
    }
    return false;
}

bool Piece::checkEat(const glm::vec3 eatPiecePos, bool canEat)
{
    for(int i(0); i < mNbEatCases; i++)
    {
        if(eatPiecePos.x >= mEatCases[i].x-1 && eatPiecePos.x <= mEatCases[i].x+1
        && eatPiecePos.z >= mEatCases[i].y-1 && eatPiecePos.z <= mEatCases[i].y+1)
        {
            if(checkValidCases(mCasesBloquesEat,i))
            {
                if(canEat)
                {
                    glm::vec3 newPos = glm::vec3(mEatCases[i].x,mMesh->getPosition().y,mEatCases[i].y);
                    setPosition(newPos);
                }
                return true;
            }
        }
    }
    return false;
}

void Piece::setActive(const bool state)
{
    isActive = state;
}

void Piece::setIntensity(const float intensity)
{
    mMesh->setAmbiantIntensity(intensity);
}

void Piece::setAlive(bool state)
{
    isAlive = state;
}

void Piece::setTexture(const std::string newTexture)
{
    mMesh->setTexture(newTexture);
}

void Piece::bloquerCases(CollisionManager *collisionMgr)
{
    std::cout << "Aucune case a bloquer" << std::endl;
}

bool Piece::checkValidCases(const std::vector<int> &casesInterdites,const int caseAVerifier)
{
    for(int i(0); i < casesInterdites.size(); i++)
    {
        if(casesInterdites[i] == caseAVerifier)
        {
            return false;
        }
    }
    return true;
}

char Piece::getTeam() const
{
    return mEquipe;
}
