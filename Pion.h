#ifndef PION_H_INCLUDED
#define PION_H_INCLUDED

#include "Piece.h"

class Pion : public Piece
{
public:
    Pion();
    Pion(char equipe,char number);
    ~Pion();

    void actualiseCases();
    void bloquerCases(CollisionManager *collisionMgr);

protected:
};

#endif // PION_H_INCLUDED
