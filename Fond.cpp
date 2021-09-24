#include "Fond.h"

Fond::Fond(glm::vec3 position,std::string texture,std::string vertShader,std::string fragShader):mShader(vertShader,fragShader),
                                                                                               mTexture(texture),
                                                                                               mVboID(0),mVaoID(0),
                                                                              mTailleVerticesBytes(18*sizeof(float)),
                                                                              mTailleCoordTextureBytes(12*sizeof(float)),mPosition(position),mScale(1,1,1)
{
    mShader.charger();
    mTexture.load();

    float verticesTmp[] = {-1,-1,position.y, 1,-1,position.y, 1,1,position.y,
                            -1,-1,position.y, -1,1,position.y, 1,1,position.y};

    float coordTextureTmp[] = {0,0,  1,0, 1,1,
                               0,0,  0,1, 1,1};

    for(int i(0);i < 18; i++)
        mVertices[i] = verticesTmp[i];

    for(int i(0); i < 12; i++)
        mCoordTexture[i] = coordTextureTmp[i];
}

Fond::~Fond()
{
    glDeleteBuffers(1,&mVboID);
    glDeleteVertexArrays(1,&mVaoID);
}

void Fond::afficher(glm::mat4 projection,glm::mat4 modelview)
{
    glUseProgram(mShader.getProgramID());
        glBindVertexArray(mVaoID);
            glm::mat4 save = modelview;
            modelview = glm::translate(modelview,mPosition);
            modelview = glm::scale(modelview,mScale);
            glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"modelview"),1,GL_FALSE,glm::value_ptr(modelview));
            glBindTexture(GL_TEXTURE_2D,mTexture.getID());
                glDrawArrays(GL_TRIANGLES,0,6);
                modelview = save;
            glBindTexture(GL_TEXTURE_2D,0);
        glBindVertexArray(0);
    glUseProgram(0);
}

void Fond::charger()
{
    if(glIsBuffer(mVboID) == GL_TRUE)
        glDeleteBuffers(1,&mVboID);

    glGenBuffers(1,&mVboID);

    glBindBuffer(GL_ARRAY_BUFFER,mVboID);
        glBufferData(GL_ARRAY_BUFFER,mTailleVerticesBytes+mTailleCoordTextureBytes,0,GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER,0,mTailleVerticesBytes,mVertices);
        glBufferSubData(GL_ARRAY_BUFFER,mTailleVerticesBytes,mTailleCoordTextureBytes,mCoordTexture);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    if(glIsVertexArray(mVaoID) == GL_TRUE)
        glDeleteVertexArrays(1,&mVaoID);

    glGenVertexArrays(1,&mVaoID);

    glBindVertexArray(mVaoID);
        glBindBuffer(GL_ARRAY_BUFFER,mVboID);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(mTailleVerticesBytes));
            glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Fond::translate(glm::vec3 vecteur)
{
    mPosition += vecteur;
}

void Fond::scale(glm::vec3 scale)
{
    mScale = scale;
}

void Fond::setPosition(glm::vec3 position)
{
    mPosition = position;
}

glm::vec3 Fond::getPosition() const
{
    int x = 3;
    return mPosition;
}

void Fond::setImgFile(std::string const &file)
{
    mTexture.setImgFile(file);
    mTexture.load();
}
