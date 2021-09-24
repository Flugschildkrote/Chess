#include "Collider.h"

Collider3D::Collider3D()
{

}

Collider3D::Collider3D(std::string name,std::string forme,glm::vec3 meshPosition)
{
    mName = name;
    mPosition = meshPosition;

    if(forme == "RECT")
    {
        mForme = forme;
    }else
    if(forme == "SPHERE")
    {
        mForme = forme;
    }
    else
    {
        std::cout << "Forme de collider invalide" << std::endl;
        return;
    }

}

Collider3D::Collider3D(std::string name,std::string forme,glm::vec3 meshPosition,glm::vec3 taille,glm::vec3 decalage)
{
    mName = name;
    mPosition = meshPosition;
    mDecalage = decalage;
    mBoxPosition = mPosition + mDecalage;

    if(forme == "RECT")
    {
        mForme = forme;
        mTaille.x = taille.x/2.0;
        mTaille.y = taille.y/2.0;
        mTaille.z = taille.z/2.0;

        mCoinAvantDroitHaut.x = mBoxPosition.x+mTaille.x;
        mCoinAvantDroitHaut.y = mBoxPosition.y+mTaille.y;
        mCoinAvantDroitHaut.z = mBoxPosition.z-mTaille.z;
        mCoinAvantDroitBas.x = mBoxPosition.x+mTaille.x;
        mCoinAvantDroitBas.y = mBoxPosition.y-mTaille.y;
        mCoinAvantDroitBas.z = mBoxPosition.z-mTaille.z;
        mCoinAvantGaucheHaut.x = mBoxPosition.x-mTaille.x;
        mCoinAvantGaucheHaut.y = mBoxPosition.y+mTaille.y;
        mCoinAvantGaucheHaut.z = mBoxPosition.z-mTaille.z;
        mCoinAvantGaucheBas.x = mBoxPosition.x-mTaille.x;
        mCoinAvantGaucheBas.y = mBoxPosition.y-mTaille.y;
        mCoinAvantGaucheBas.z = mBoxPosition.z-mTaille.z;
        mCoinArriereDroitHaut.x = mBoxPosition.x+mTaille.x;
        mCoinArriereDroitHaut.y = mBoxPosition.y+mTaille.y;
        mCoinArriereDroitHaut.z = mBoxPosition.z+mTaille.z;
        mCoinArriereDroitBas.x = mBoxPosition.x+mTaille.x;
        mCoinArriereDroitBas.y = mBoxPosition.y-mTaille.y;
        mCoinArriereDroitBas.z = mBoxPosition.z+mTaille.z;
        mCoinArriereGaucheHaut.x = mBoxPosition.x-mTaille.x;
        mCoinArriereGaucheHaut.y = mBoxPosition.y+mTaille.y;
        mCoinArriereGaucheHaut.z = mBoxPosition.z+mTaille.z;
        mCoinArriereGaucheBas.x = mBoxPosition.x-mTaille.x;
        mCoinArriereGaucheBas.y = mBoxPosition.y-mTaille.y;
        mCoinArriereGaucheBas.z = mBoxPosition.z+mTaille.z;

        //std::cout << mCoinAvantGaucheHaut.x << ";" << mCoinAvantGaucheHaut.y << ";" << mCoinAvantGaucheHaut.z << std::endl;
        mNormalFaceAvant = glm::vec3(0,0,-1);
        mNormalFaceArriere = glm::vec3(0,0,1);
        mNormalFaceGauche = glm::vec3(-1,0,0);
        mNormalFaceDroite = glm::vec3(1,0,0);
        mNormalFaceHaut = glm::vec3(0,1,0);
        mNormalFaceBas = glm::vec3(0,-1,0);

            /* Ordre des plans :
            0 : avant
            1 : arriere
            2 : gauche
            3 droite
            4 haut
            5 bas*/
        equaPlan_a.clear();
        equaPlan_b.clear();
        equaPlan_c.clear();
        equaPlan_d.clear();

        equaPlan_a.push_back(mNormalFaceAvant.x);
        equaPlan_b.push_back(mNormalFaceAvant.y);
        equaPlan_c.push_back(mNormalFaceAvant.z);
        equaPlan_d.push_back((-mCoinAvantGaucheBas.x*mNormalFaceAvant.x)+(-mCoinAvantGaucheBas.y*mNormalFaceAvant.y)+(-mCoinAvantGaucheBas.z*mNormalFaceAvant.z));

        equaPlan_a.push_back(mNormalFaceArriere.x);
        equaPlan_b.push_back(mNormalFaceArriere.y);
        equaPlan_c.push_back(mNormalFaceArriere.z);
        equaPlan_d.push_back((-mCoinArriereDroitBas.x*mNormalFaceArriere.x)+(-mCoinArriereDroitBas.y*mNormalFaceArriere.y)+(-mCoinArriereDroitBas.z*mNormalFaceArriere.z));

        equaPlan_a.push_back(mNormalFaceGauche.x);
        equaPlan_b.push_back(mNormalFaceGauche.y);
        equaPlan_c.push_back(mNormalFaceGauche.z);
        equaPlan_d.push_back((-mCoinArriereGaucheBas.x*mNormalFaceGauche.x)+(-mCoinArriereGaucheBas.y*mNormalFaceGauche.y)+(-mCoinArriereGaucheBas.z*mNormalFaceGauche.z));

        equaPlan_a.push_back(mNormalFaceDroite.x);
        equaPlan_b.push_back(mNormalFaceDroite.y);
        equaPlan_c.push_back(mNormalFaceDroite.z);
        equaPlan_d.push_back((-mCoinAvantDroitBas.x*mNormalFaceDroite.x)+(-mCoinAvantDroitBas.y*mNormalFaceDroite.y)+(-mCoinAvantDroitBas.z*mNormalFaceDroite.z));

        equaPlan_a.push_back(mNormalFaceHaut.x);
        equaPlan_b.push_back(mNormalFaceHaut.y);
        equaPlan_c.push_back(mNormalFaceHaut.z);
        equaPlan_d.push_back((-mCoinAvantGaucheHaut.x*mNormalFaceHaut.x)+(-mCoinAvantGaucheHaut.y*mNormalFaceHaut.y)+(-mCoinAvantGaucheHaut.z*mNormalFaceHaut.z));

        equaPlan_a.push_back(mNormalFaceBas.x);
        equaPlan_b.push_back(mNormalFaceBas.y);
        equaPlan_c.push_back(mNormalFaceBas.z);
        equaPlan_d.push_back((-mCoinArriereGaucheBas.x*mNormalFaceBas.x)+(-mCoinArriereGaucheBas.y*mNormalFaceBas.y)+(-mCoinArriereGaucheBas.z*mNormalFaceBas.z));

    }
    else if(forme == "CUBE")
    {
        mForme = forme;
        mTaille.x = taille.x/2.0;
        mTaille.y = taille.y/2.0;
        mTaille.z = taille.z/2.0;

        mRectArrayBis.clear();
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x, mBoxPosition.y, mBoxPosition.z));
    }
    else
    if(forme == "SPHERE")
    {
        mForme = forme;
        mRadius = taille.x;
    }
    else
    {
        std::cout << "Forme de collider invalide" << std::endl;
        return;
    }

}


Collider3D::~Collider3D()
{

}

void Collider3D::setRectSize(glm::vec3 taille,glm::vec3 decalage)
{
    if(mForme == "RECT" || mForme == "CUBE")
    {
        mTaille.x = taille.x/2.0;
        mTaille.y = taille.y/2.0;
        mTaille.z = taille.z/2.0;
        mDecalage = decalage;
    }
    else
        std::cout << "Fonction non adaptee a la forme de collider : " << mForme << std::endl;
}

void Collider3D::setSphereRadius(float radius)
{
    if(mForme == "SPHERE")
        mRadius = radius;
    else
    std::cout << "Fonction non adaptee a la forme de collider : " << mForme << std::endl;
}

void Collider3D::setName(std::string newName)
{
    mName = newName;
}

void Collider3D::actualizePosition(glm::vec3 newPosition)
{
    mPosition = newPosition;
    mBoxPosition = mPosition + mDecalage;

    if(mForme == "CUBE")
    {
        mRectArrayBis.clear();
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z-mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y+mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x+mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x-mTaille.x, mBoxPosition.y-mTaille.y, mBoxPosition.z+mTaille.z));
        mRectArrayBis.push_back(glm::vec3(mBoxPosition.x, mBoxPosition.y, mBoxPosition.z));
    }
    else if(mForme == "RECT")
    {
        mCoinAvantDroitHaut.x = mBoxPosition.x+mTaille.x;
        mCoinAvantDroitHaut.y = mBoxPosition.y+mTaille.y;
        mCoinAvantDroitHaut.z = mBoxPosition.z-mTaille.z;
        mCoinAvantDroitBas.x = mBoxPosition.x+mTaille.x;
        mCoinAvantDroitBas.y = mBoxPosition.y-mTaille.y;
        mCoinAvantDroitBas.z = mBoxPosition.z-mTaille.z;
        mCoinAvantGaucheHaut.x = mBoxPosition.x-mTaille.x;
        mCoinAvantGaucheHaut.y = mBoxPosition.y+mTaille.y;
        mCoinAvantGaucheHaut.z = mBoxPosition.z-mTaille.z;
        mCoinAvantGaucheBas.x = mBoxPosition.x-mTaille.x;
        mCoinAvantGaucheBas.y = mBoxPosition.y-mTaille.y;
        mCoinAvantGaucheBas.z = mBoxPosition.z-mTaille.z;
        mCoinArriereDroitHaut.x = mBoxPosition.x+mTaille.x;
        mCoinArriereDroitHaut.y = mBoxPosition.y+mTaille.y;
        mCoinArriereDroitHaut.z = mBoxPosition.z+mTaille.z;
        mCoinArriereDroitBas.x = mBoxPosition.x+mTaille.x;
        mCoinArriereDroitBas.y = mBoxPosition.y-mTaille.y;
        mCoinArriereDroitBas.z = mBoxPosition.z+mTaille.z;
        mCoinArriereGaucheHaut.x = mBoxPosition.x-mTaille.x;
        mCoinArriereGaucheHaut.y = mBoxPosition.y+mTaille.y;
        mCoinArriereGaucheHaut.z = mBoxPosition.z+mTaille.z;
        mCoinArriereGaucheBas.x = mBoxPosition.x-mTaille.x;
        mCoinArriereGaucheBas.y = mBoxPosition.y-mTaille.y;
        mCoinArriereGaucheBas.z = mBoxPosition.z+mTaille.z;

        mNormalFaceAvant = glm::vec3(0,0,-1);
        mNormalFaceArriere = glm::vec3(0,0,1);
        mNormalFaceGauche = glm::vec3(-1,0,0);
        mNormalFaceDroite = glm::vec3(1,0,0);
        mNormalFaceHaut = glm::vec3(0,-1,0);
        mNormalFaceBas = glm::vec3(0,1,0);


            /* Ordre des plans :
            0 : avant
            1 : arriere
            2 : gauche
            3 droite
            4 haut
            5 bas*/

        equaPlan_a.clear();
        equaPlan_b.clear();
        equaPlan_c.clear();
        equaPlan_d.clear();

        equaPlan_a.push_back(mNormalFaceAvant.x);
        equaPlan_b.push_back(mNormalFaceAvant.y);
        equaPlan_c.push_back(mNormalFaceAvant.z);
        equaPlan_d.push_back((-mCoinAvantGaucheBas.x*mNormalFaceAvant.x)+(-mCoinAvantGaucheBas.y*mNormalFaceAvant.y)+(-mCoinAvantGaucheBas.z*mNormalFaceAvant.z));

        equaPlan_a.push_back(mNormalFaceArriere.x);
        equaPlan_b.push_back(mNormalFaceArriere.y);
        equaPlan_c.push_back(mNormalFaceArriere.z);
        equaPlan_d.push_back((-mCoinArriereDroitBas.x*mNormalFaceArriere.x)+(-mCoinArriereDroitBas.y*mNormalFaceArriere.y)+(-mCoinArriereDroitBas.z*mNormalFaceArriere.z));

        equaPlan_a.push_back(mNormalFaceGauche.x);
        equaPlan_b.push_back(mNormalFaceGauche.y);
        equaPlan_c.push_back(mNormalFaceGauche.z);
        equaPlan_d.push_back((-mCoinArriereGaucheBas.x*mNormalFaceGauche.x)+(-mCoinArriereGaucheBas.y*mNormalFaceGauche.y)+(-mCoinArriereGaucheBas.z*mNormalFaceGauche.z));

        equaPlan_a.push_back(mNormalFaceDroite.x);
        equaPlan_b.push_back(mNormalFaceDroite.y);
        equaPlan_c.push_back(mNormalFaceDroite.z);
        equaPlan_d.push_back((-mCoinAvantDroitBas.x*mNormalFaceDroite.x)+(-mCoinAvantDroitBas.y*mNormalFaceDroite.y)+(-mCoinAvantDroitBas.z*mNormalFaceDroite.z));

        equaPlan_a.push_back(mNormalFaceHaut.x);
        equaPlan_b.push_back(mNormalFaceHaut.y);
        equaPlan_c.push_back(mNormalFaceHaut.z);
        equaPlan_d.push_back((-mCoinAvantGaucheHaut.x*mNormalFaceHaut.x)+(-mCoinAvantGaucheHaut.y*mNormalFaceHaut.y)+(-mCoinAvantGaucheHaut.z*mNormalFaceHaut.z));

        equaPlan_a.push_back(mNormalFaceBas.x);
        equaPlan_b.push_back(mNormalFaceBas.y);
        equaPlan_c.push_back(mNormalFaceBas.z);
        equaPlan_d.push_back((-mCoinArriereGaucheBas.x*mNormalFaceBas.x)+(-mCoinArriereGaucheBas.y*mNormalFaceBas.y)+(-mCoinArriereGaucheBas.z*mNormalFaceBas.z));
    }
}

bool Collider3D::checkRayCollision(glm::vec3 rayStart, glm::vec3 rayEnd)
{

    if(mForme == "RECT")
    {
        equa_droite_x.x = (rayEnd.x-rayStart.x);
        equa_droite_y.x = (rayEnd.y-rayStart.y);
        equa_droite_z.x = (rayEnd.z-rayStart.z);

        equa_droite_x.y = rayStart.x;
        equa_droite_y.y = rayStart.y;
        equa_droite_z.y = rayStart.z;

        result.clear();
        collidePoint.clear();

        for(int i(0); i < 6; i++)
        {
            float a = (equaPlan_a[i]*equa_droite_x.x)+(equaPlan_b[i]*equa_droite_y.x)+(equaPlan_c[i]*equa_droite_z.x);
            float b = (equaPlan_a[i]*equa_droite_x.y)+(equaPlan_b[i]*equa_droite_y.y)+(equaPlan_c[i]*equa_droite_z.y)+equaPlan_d[i];
            float t = (-b)/a;
            result.push_back(t);

            glm::vec3 resultat;
            resultat.x = (equa_droite_x.x*t)+rayStart.x;
            resultat.y = (equa_droite_y.x*t)+rayStart.y;
            resultat.z = (equa_droite_z.x*t)+rayStart.z;
            collidePoint.push_back(resultat);

        }
        std::vector<float> tabl;
        for(int i(0); i < collidePoint.size();i++)
        {
             if(collidePoint[i].x >= (mBoxPosition.x-mTaille.x-0.001) && (collidePoint[i].x) <= (mBoxPosition.x+mTaille.x+0.001) &&
                collidePoint[i].y >= (mBoxPosition.y-mTaille.y-0.001) && (collidePoint[i].y) <=  (mBoxPosition.y+mTaille.y+0.001) &&
                collidePoint[i].z >= (mBoxPosition.z-mTaille.z-0.001) && (collidePoint[i].z) <= (mBoxPosition.z+mTaille.z+0.001))
            {
                 tabl.push_back(result[i]);
            }

            /**//**//**//*Methode de base*//**//**/
            /*
            if(i == 0 || i == 1)
            {
                if(collidePoint[i].x >= (mBoxPosition.x-mTaille.x) && (collidePoint[i].x) <= (mBoxPosition.x+mTaille.x) &&
                   collidePoint[i].y >= (mBoxPosition.y-mTaille.y) && (collidePoint[i].y) <=  (mBoxPosition.y+mTaille.y))
                {
                    tabl.push_back(result[i]);
                   // std::cout << i << " ____ " << collidePoint[i].x << ";" << collidePoint[i].y << ";" << collidePoint[i].z << std::endl;
                }
            }
            else if(i == 2 || i == 3)
            {
                if(collidePoint[i].y >= (mBoxPosition.y-mTaille.y) && collidePoint[i].y <= (mBoxPosition.y+mTaille.y) &&
                   collidePoint[i].z >= (mBoxPosition.z-mTaille.z) && collidePoint[i].z <= (mBoxPosition.z+mTaille.z))
                {
                    tabl.push_back(result[i]);
                    //std::cout << i << " ____ " << collidePoint[i].x << ";" << collidePoint[i].y << ";" << collidePoint[i].z << std::endl;
                }
            }
            else if(i == 4 || i == 5)
            {
                if(collidePoint[i].x >= (mBoxPosition.x-mTaille.x) && collidePoint[i].x <= (mBoxPosition.x+mTaille.x) &&
                   collidePoint[i].z >= (mBoxPosition.z-mTaille.z) && collidePoint[i].z <= (mBoxPosition.z+mTaille.z))
                {
                    tabl.push_back(result[i]);
                    //std::cout << result[i] << std::endl;
                 //   std::cout << mBoxPosition.y-mTaille.y << "   " << mBoxPosition.y+mTaille.y << std::endl;
                  //std::cout << i << " ____ " << collidePoint[i].x << ";" << collidePoint[i].y << ";" << collidePoint[i].z << std::endl;
                }
            }*//**//**//**/
        }
        if(tabl.size() != 0)
        {
            float nearestResult;
            for(int i(0); i < tabl.size(); i++)
            {
               // std::cout << tabl[i] << std::endl;
                if(i == 0)
                {
                    nearestResult = tabl[0];
                }
                else if(nearestResult > tabl[i])
                {
                    nearestResult = tabl[i];
                }
            }
           // std::cout << nearestResult << std::endl;
            for(int i(0); i < result.size(); i++)
            {
                if(result[i] == nearestResult)
                {
                    mLastCollide = collidePoint[i];
                    //std::cout << collidePoint[i].x << ";" << collidePoint[i].y << ";" << collidePoint[i].z << std::endl;
                }
            }
             return true;
        }
        else
            return false;

    }else
    if(mForme == "CUBE")
    {
        for(int i(0); i < 8;i++)
        {
            glm::vec3 A,B,O,AB,AO,R;
            float S;
            A = rayStart;
            B = rayEnd;
            O = mRectArrayBis[i];
            AB = B-A;
            AO = O-A;
            S = ((AB.x*AO.x)+(AB.y*AO.y)+(AB.z*AO.z))/((AB.x*AB.x)+(AB.y*AB.y)+(AB.z*AB.z));
            R.x = (AB.x*S)+A.x;
            R.y = (AB.y*S)+A.y;
            R.z = (AB.z*S)+A.z;
            glm::vec3 boxMax = mPosition+mTaille;
            glm::vec3 boxMin = mPosition-mTaille;

            if(R.x >= boxMin.x && R.x <= boxMax.x && R.y >= boxMin.y && R.y <= boxMax.y && R.z >= boxMin.z && R.z <= boxMax.z)
            {
                mLastCollide = R;
                return true;
            }
        }
    }else
    if(mForme == "SPHERE")
    {
        glm::vec3 A,B,O,AB,AO,R;
        float S;
        A = rayStart;
        B = rayEnd;
        O = mBoxPosition;
        AB = B-A;
        AO = O-A;
        S = ((AB.x*AO.x)+(AB.y*AO.y)+(AB.z*AO.z))/((AB.x*AB.x)+(AB.y*AB.y)+(AB.z*AB.z));
        R.x = (AB.x*S)+A.x;
        R.y = (AB.y*S)+A.y;
        R.z = (AB.z*S)+A.z;

        float norme = (float) sqrt((R.x*R.x)+(R.y*R.y)+(R.z*R.z));

        if(norme <= mRadius)
        {
            mLastCollide = R;
            return true;
        }
    }
    return false;
}

glm::vec3 Collider3D::getHitRayPosition() const
{
    return mLastCollide;
}

glm::vec3 Collider3D::getPosition() const
{
    return mPosition;
}

std::string Collider3D::getName() const
{
    return mName;
}
