#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Texture
{
public:
    Texture();
    Texture(std::string file);
    Texture(Texture const &textureACopier);
    Texture(int largeur,int hauteur,GLenum format,GLenum formatInterne,bool textureVide);
    Texture& operator=(Texture const &textureACopier);
    ~Texture();

    bool load();
    GLint getID();
    void chargerTextureVide();
    void setImgFile(const std::string &file);
    SDL_Surface* inverserImage(SDL_Surface *sourceImg) const;

private:
    GLuint mId;
    std::string mFile;

    int mLargeur;
    int mHauteur;
    GLenum mFormat;
    GLenum mFormatInterne;
    bool mTextureVide;
    SDL_Surface mImageInverse;
};

#endif // TEXTURE_H_INCLUDED
