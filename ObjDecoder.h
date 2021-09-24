#ifndef OBJDECODER_H_INCLUDED
#define OBJDECODER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class OBJDecoder
{
public:
    OBJDecoder(std::string fichierSource);
    ~OBJDecoder();

    void lireFichier();
    std::vector<std::vector<float> > getAnimation(int anim);

    std::vector<float> getVertices() const;
    std::vector<float> getCoordTexture() const;
    std::vector<float> getNormals() const;

    int getNombreAnims() const;

private:
    std::ifstream mFichierSource;
    std::vector<float> mVertices;
    std::vector<float> mCoordTexture;
    std::vector<float> mNormals;
    std::vector<float> mFinalVertices;
    std::vector<float> mFinalCoordText;
    std::vector<float> mFinalNormals;
    std::vector<float> mCurrentFrame;

    int mNombreAnimations;
};

#endif // OBJDECODER_H_INCLUDED
