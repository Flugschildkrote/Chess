#ifndef ROI_H_INCLUDED
#define ROI_H_INCLUDED

#include "Piece.h"

class Roi : public Piece
{
public:

    Roi(char equipe);
    ~Roi();

    void actualiseCases();
    void bloquerCases(CollisionManager *collisionMgr);

protected:

};

#endif // ROI_H_INCLUDED
