#ifndef REINE_H_INCLUDED
#define REINE_H_INCLUDED

#include "Piece.h"

class Reine : public Piece
{
public:
    Reine(char equipe);
    ~Reine();

    void actualiseCases();
    void bloquerCases(CollisionManager *collisionMgr);

protected:

};

#endif // REINE_H_INCLUDED
