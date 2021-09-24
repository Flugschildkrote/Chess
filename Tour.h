#ifndef TOUR_H_INCLUDED
#define TOUR_H_INCLUDED

#include "Piece.h"

class Tour : public Piece
{
public:
    Tour(char equipe, char side);
    ~Tour();

    void actualiseCases();
    void bloquerCases(CollisionManager *collisionMgr);

protected:

};

#endif // TOUR_H_INCLUDED
