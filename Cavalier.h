#ifndef CAVALIER_H_INCLUDED
#define CAVALIER_H_INCLUDED

#include "Piece.h"

class Cavalier: public Piece
{
public:
    Cavalier(char equipe, char side);
    ~Cavalier();

    void actualiseCases();
    void bloquerCases(CollisionManager *collisionMgr);

protected:
};

#endif // CAVALIER_H_INCLUDED
