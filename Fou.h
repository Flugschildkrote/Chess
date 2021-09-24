#ifndef FOU_H_INCLUDED
#define FOU_H_INCLUDED

#include "Piece.h"

class Fou : public Piece
{
public:
    Fou(char equipe, char side);
    ~Fou();

    void actualiseCases();
    void bloquerCases(CollisionManager *collisionMgr);

protected:

};


#endif // FOU_H_INCLUDED
