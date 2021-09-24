#include "ObjDecoder.h"

using namespace std;

OBJDecoder::OBJDecoder(std::string fichierSource):mFichierSource(fichierSource.c_str(),ios::in)
{
    if(!mFichierSource)
        cout << "Impossible d'ouvrir \"" << fichierSource << "\"" << endl;
}

OBJDecoder::~OBJDecoder()
{

}

void OBJDecoder::lireFichier()
{
    mNombreAnimations = 0;
    char lecture;
    string characteres("");
    int compt(0);

    while (characteres != "FIN")
    {
        //std::cout << "ok" << std::endl;
        compt++;
        mFichierSource.get(lecture);
        if(lecture == ' ' || lecture == '\n')
        {
            if(characteres == "vt")
            {
                float coordX;
                float coordY;
                mFichierSource >> coordX >> coordY;
                mCoordTexture.push_back(coordX);
                mCoordTexture.push_back(coordY);
            }
            else if(characteres == "vn")
            {
                float normalX;
                float normalY;
                float normalZ;
                mFichierSource >> normalX >> normalY >> normalZ;
                mNormals.push_back(normalX);
                mNormals.push_back(normalY);
                mNormals.push_back(normalZ);
            }
            else if(characteres == "v")
            {
                float vertexX;
                float vertexY;
                float vertexZ;
                mFichierSource >> vertexX >> vertexY >> vertexZ;
                mVertices.push_back(vertexX);
                mVertices.push_back(vertexY);
                mVertices.push_back(vertexZ);
            }
            else if(characteres == "at")
            {
                mFichierSource >> mNombreAnimations;
            }
            else if(characteres == "f")
            {
                //Pour une face
                char slash;
                int vertex;
                int coordText;
                int normals;

                //Pour chaque bloc de la face ( v/vt/vn )
                for(int compteurVertex(0); compteurVertex < 3;compteurVertex ++)
                {
                    // Prend le vertex
                    mFichierSource >> vertex;
                    int vertexIndice = (vertex-1)*3;
                    for(int i(0);i < 3; i++)
                    {
                        //vertex.x,vertex.y,vertex.z
                        mFinalVertices.push_back(mVertices[vertexIndice+i]);
                    }

                    mFichierSource.get(slash);

                    mFichierSource >> coordText;
                    int coordIndice = (coordText-1)*2;
                    for(int i(0);i < 2; i++)
                    {
                        mFinalCoordText.push_back(mCoordTexture[coordIndice+i]);
                    }

                    mFichierSource.get(slash);

                    mFichierSource >> normals;
                    int normalsIndice = (normals-1)*3;
                    for(int i(0); i < 3; i++)
                    {
                        mFinalNormals.push_back(mNormals[normalsIndice+i]);
                    }
                }
            }
            characteres = "";
        }
        else
        {
            characteres += lecture;
        }
    }
           /*Affichage des vertices*/
   /* int compteurV(0);
    cout << "[Vertices]" << endl;
    cout << "v0 : ";
    for(unsigned int i(0);i < mVertices.size();i++)
    {
        if(compteurV == 3)
        {
            cout << endl << "v" << (i/3) << " : ";
            compteurV = 0;
        }
        cout << mVertices[i] << ",";
        compteurV++;
    }

    cout << endl;*/
        /*Affichage des coordonée de textures*/
    /*int compteurTex(0);
    cout << "[Texture]" << endl;
    cout << "t0 : ";
    for(unsigned int i(0);i < mCoordTexture.size();i++)
    {
        if(compteurTex == 2)
        {
            cout << endl << "t" << (i/2) << " : ";
            compteurTex = 0;
        }
        cout << mCoordTexture[i] << ",";
        compteurTex++;
    }

    cout << endl;*/
    /*Affichage des normales*/
    /*int compteurN(0);
    cout << "[Normals]" << endl;
    cout << "n0 : ";
    for(unsigned int i(0);i < mNormals.size();i++)
    {
        if(compteurN == 3)
        {
            cout << endl << "n" << (i/3) << " : ";
            compteurN = 0;
        }
        cout << mNormals[i] << ",";
        compteurN++;
    }
    cout << endl;*/
      /*Affichage du tableau coord final*/
    /*int compteurCT(0);
    cout << "[FinalTexture]" << endl;
    cout << "t0 : ";
    for(unsigned int i(0); i < mFinalCoordText.size();i++)
    {
        if(compteurCT == 2)
        {
            cout << endl << "t" << (i/2) << " : ";
            compteurCT = 0;
        }
        cout << mFinalCoordText[i] << ",";
        compteurCT++;
    }*/
    mFichierSource.close();
}

std::vector<std::vector<float> > OBJDecoder::getAnimation(int anim)
{
    /**//*Lire le num de l'anim correspondant*//**/
    /**//*Ajouter les vertices dans un tableau*//**/
    /**//*Ajouter les vertices dans la bonne frame(tableau int** ou int[][]*//**/
    /**/ /*s'arreter a l'animation suivante*/
    std::vector<std::vector<float> > animationArray;
    std::vector<std::vector<float> > animationArrayFinal;

    float tableauTemp[40][5000]; /**//**/ /*a modifier tableau[nombre de frame][vertices]*/
    int compteurFrame(0);
    int nombreDeFrame(0);
    char lecture;
    string characteres("");
    int compt(0);
    bool stopper = false;
    int frameID;
    int animID;


    //while (!stopper)
    while (characteres != "FIN")
    {
        compt++;
        mFichierSource.get(lecture);

        if(lecture == ' ' || lecture == '\n')
        {
            if(characteres == "ANIMATION")
            {
                //int indice;
                mFichierSource >> animID;
                /*if(indice > anim)
                {
                    stopper = true;
                    animationArray.push_back(mCurrentFrame);
                    mCurrentFrame.clear();
                }*/
            }
            else if(characteres == "FANIMATION")
            {
                int finAnimID;
                mFichierSource >> finAnimID;
                if(finAnimID == anim)
                {
                    stopper = true;
                    animationArray.push_back(mCurrentFrame);
                    mCurrentFrame.clear();
                }
            }
            else if(characteres == "FRAME")
            {
                nombreDeFrame ++;
                if(animID == anim)
                {
                    mFichierSource >> frameID;

                    if(frameID != 0)
                    {
                        animationArray.push_back(mCurrentFrame);
                        mCurrentFrame.clear();
                    }
                }
            }
            else if(characteres == "a")
            {
                if(animID == anim)
                {
                    float vertexX;
                    float vertexY;
                    float vertexZ;
                    mFichierSource >> vertexX >> vertexY >> vertexZ;
                    mCurrentFrame.push_back(vertexX);
                    mCurrentFrame.push_back(vertexY);
                    mCurrentFrame.push_back(vertexZ);
                }
            }
            else if(characteres == "f")
            {
                char slash;
                int vertex;
                int coordText;
                int normals;

                for(int compteurVertex(0); compteurVertex < 3;compteurVertex ++)
                {
                    mFichierSource >> vertex;
                    int vertexIndice = (vertex-1)*3;
                    for(int i(0);i < 3; i++)
                    {
                        for(int j(0); j < animationArray.size();j++)
                        {
                            tableauTemp[j][compteurFrame] = animationArray[j][vertexIndice+i];
                        }
                        compteurFrame ++;
                    }
                    mFichierSource.get(slash);

                    mFichierSource >> coordText;
                    int coordIndice = (coordText-1)*2;
                    /*for(int i(0);i < 2; i++)
                    {
                        mFinalCoordText.push_back(mCoordTexture[coordIndice+i]);
                    }*/

                    mFichierSource.get(slash);

                    mFichierSource >> normals;
                }
            }
            characteres = "";
        }
        else
        {
            characteres += lecture;
        }
    }
    //int c = true;
    for(int i(0); i < nombreDeFrame ; i++)
    {
        vector<float> tmpArray;
        for(int j(0); j < compteurFrame; j++)
        {
            tmpArray.push_back(tableauTemp[i][j]);
            /*if(c)
            {
                cout << tableauTemp[30][99] << " " << tableauTemp[30][100] << " " << tableauTemp[30][101] << endl;
                cout << tableauTemp[30][102] << " " << tableauTemp[30][103] << " " << tableauTemp[30][104] << endl;
                cout << tableauTemp[30][105] << " " << tableauTemp[30][106] << " " << tableauTemp[30][107] << endl;
            }
            c = false;*/
       }
        animationArrayFinal.push_back(tmpArray);
        tmpArray.clear();
    }
    return animationArrayFinal;
}

std::vector<float> OBJDecoder::getVertices() const
{
    return mFinalVertices;
}

std::vector<float> OBJDecoder::getCoordTexture() const
{
    return mFinalCoordText;
}

std::vector<float> OBJDecoder::getNormals() const
{
    return mFinalNormals;
}

int OBJDecoder::getNombreAnims() const
{
    return mNombreAnimations;
}
