#include "Texture.h"

Texture::Texture():mId(0),mFile(""),mLargeur(0),mHauteur(0),mFormat(0),mFormatInterne(0),mTextureVide(false)
{

}

Texture::Texture(std::string file):mId(0),mFile(file),mLargeur(0),mHauteur(0),mFormat(0),mFormatInterne(0),mTextureVide(false)
{

}

Texture::Texture(Texture const &textureACopier)
{
    mFile = textureACopier.mFile;
    mLargeur = textureACopier.mLargeur;
    mHauteur = textureACopier.mHauteur;
    mFormat = textureACopier.mFormat;
    mFormatInterne = textureACopier.mFormatInterne;
    mTextureVide = textureACopier.mTextureVide;

    if(mTextureVide && glIsTexture(textureACopier.mId) == GL_TRUE)
    chargerTextureVide();
    else if(glIsTexture(textureACopier.mId) == GL_TRUE)
    load();
}

Texture::Texture(int largeur,int hauteur,
                 GLenum format,GLenum formatInterne,bool textureVide):mId(0),mFile(""),
                                                                      mLargeur(largeur),mHauteur(hauteur),mFormat(format),
                                                                      mFormatInterne(formatInterne),mTextureVide(textureVide)
{

}

Texture& Texture::operator=(Texture const &textureACopier)
{
    mFile = textureACopier.mFile;
    mLargeur = textureACopier.mLargeur;
    mHauteur = textureACopier.mHauteur;
    mFormat = textureACopier.mFormat;
    mFormatInterne = textureACopier.mFormatInterne;
    mTextureVide = textureACopier.mTextureVide;

    if(mTextureVide == true && glIsTexture(textureACopier.mId)  == GL_TRUE)
        chargerTextureVide();
    else if(glIsTexture(textureACopier.mId)  == GL_TRUE)
    load();

    return *this;
}

void Texture::chargerTextureVide()
{
    if(glIsTexture(mId)  == GL_TRUE)
        glDeleteTextures(1, &mId);

    glGenTextures(1,&mId);

    glBindTexture(GL_TEXTURE_2D,mId);
        glTexImage2D(GL_TEXTURE_2D,0,mFormatInterne, mLargeur, mHauteur, 0,mFormat, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1,&mId);
}

bool Texture::load()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    SDL_Surface *img = IMG_Load(mFile.c_str());

    if(img == 0)
    {
        std::cout << "Erreur : " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Surface *imageInverse = inverserImage(img);
    SDL_FreeSurface(img);

    if(glIsTexture(mId) == GL_TRUE)
        glDeleteTextures(1,&mId);

    glGenTextures(1,&mId);
    glBindTexture(GL_TEXTURE_2D,mId);

    GLenum imgIntFormat(0);
    GLenum imgFormat(0);

    if(imageInverse->format->BytesPerPixel == 3)
    {
        imgIntFormat = GL_RGB;

        if(imageInverse->format->Rmask == 0xff)
        {
            imgFormat = GL_RGB;
        }
        else
        {
            imgFormat = GL_BGR;
        }
    }
    else if(imageInverse->format->BytesPerPixel == 4)
    {
        imgIntFormat = GL_RGBA;
        if(imageInverse->format->Rmask == 0xff)
        {
            imgFormat = GL_RGBA;
        }
        else
        {
            imgFormat = GL_BGRA;
        }
    }

    else
    {
        std::cout << "Erreur : format de l'image inconnu" << std::endl;
        SDL_FreeSurface(imageInverse);
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D,0,imgIntFormat,imageInverse->w,imageInverse->h,0,imgFormat,GL_UNSIGNED_BYTE,imageInverse->pixels);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D,0);

    SDL_FreeSurface(imageInverse);
    return true;
}

GLint Texture::getID()
{
    return mId;
}

void Texture::setImgFile(const std::string &file)
{
    mFile = file;
}

SDL_Surface* Texture::inverserImage(SDL_Surface *imageSource) const
{
    SDL_Surface *imageInversee = SDL_CreateRGBSurface(0,imageSource->w, imageSource->h, imageSource->format->BitsPerPixel,
                                                      imageSource->format->Rmask, imageSource->format->Gmask,
                                                      imageSource->format->Bmask, imageSource->format->Amask);


    unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
    unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;


    for(int i = 0; i < imageSource->h; i++)
    {
        for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
        pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] =
        pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
    }
    return imageInversee;
}
