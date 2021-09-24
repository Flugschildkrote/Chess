#include "GUI_Text.h"

GUI_Text::GUI_Text(){}

GUI_Text::GUI_Text(const std::string texte,const glm::vec3 pointHautGauche, const glm::vec3 pointBasDroit): mText(texte), mVaoID(0), mVboID(0), mTailleVerticesBytes(0), mTailleCoordTextureBytes(0), mShow(true)
{
    int longueurTexte = texte.size();
    float longueurTotale = pointBasDroit.x-pointHautGauche.x;
    float longueurChar = (float) longueurTotale/longueurTexte;
    float lgCharTexture = (float) 1/16;

    for(int i(0); i < longueurTexte; i++)
    {
        char charactere = texte[i];
        float colone = (charactere%16)/16.0f;
        float ligne = (charactere/16)/16.0f;
        //std::cout << charactere << " : " << colone << ", " << ligne << std::endl;
        for(int j(0); j < 18; j++)
        {
            int ij = i*18;
            int ik = i*12;
            //Triangle 1
            mVertices[ij] = pointHautGauche.x +(i*longueurChar);
            mVertices[ij+1] = pointHautGauche.y;
            mVertices[ij+2] = pointHautGauche.z;
            mCoordTexture[ik] = colone;
            mCoordTexture[ik+1] = 1.0f - ligne;

            mVertices[ij+3] = pointHautGauche.x +(i*longueurChar)+(longueurChar);
            mVertices[ij+4] = pointHautGauche.y;
            mVertices[ij+5] = pointHautGauche.z;
            mCoordTexture[ik+2] = colone+(lgCharTexture/4);
            mCoordTexture[ik+3] = 1.0f - ligne;

            mVertices[ij+6] = pointHautGauche.x +(i*longueurChar);
            mVertices[ij+7] = pointBasDroit.y;
            mVertices[ij+8] = pointHautGauche.z;
            mCoordTexture[ik+4] = colone;
            mCoordTexture[ik+5] = 1.0f - ligne-(lgCharTexture/1.5);

            //Triangle 2
            mVertices[ij+9] = mVertices[ij+6];
            mVertices[ij+10] = mVertices[ij+7];
            mVertices[ij+11] = mVertices[ij+8];
            mCoordTexture[ik+6] = mCoordTexture[ik+4];
            mCoordTexture[ik+7] = mCoordTexture[ik+5];

            mVertices[ij+12] = pointHautGauche.x +(i*longueurChar)+(longueurChar);
            mVertices[ij+13] = pointBasDroit.y;
            mVertices[ij+14] = pointHautGauche.z;
            mCoordTexture[ik+8] = colone+(lgCharTexture/4);
            mCoordTexture[ik+9] = 1.0f - ligne- (lgCharTexture/1.5);

            mVertices[ij+15] =  mVertices[ij+3];
            mVertices[ij+16] =  mVertices[ij+4];
            mVertices[ij+17] =  mVertices[ij+5];
            mCoordTexture[ik+10] = mCoordTexture[ik+2];
            mCoordTexture[ik+11] = mCoordTexture[ik+3];
        }
    }

    mNbVertices = texte.size()*6;
    mTailleVerticesBytes = sizeof(float)*mNbVertices*3;
    mTailleCoordTextureBytes = sizeof(float)*mNbVertices*2;
}

GUI_Text::~GUI_Text()
{
    glDeleteBuffers(1,&mVboID);
    glDeleteVertexArrays(1,&mVaoID);
}

void GUI_Text::afficher(Texture &texture,const glm::mat4 &projection, const Shader &shader)
{
    if(mShow)
    {
        glm::mat4 modelviewProjection = projection*projection;
        glUseProgram(shader.getProgramID());
            glBindVertexArray(mVaoID);
                glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(),"modelviewProjection"), 1, GL_FALSE, glm::value_ptr(modelviewProjection));
                glBindTexture(GL_TEXTURE_2D,texture.getID());
                    glDrawArrays(GL_TRIANGLES,0,mNbVertices);
                glBindTexture(GL_TEXTURE_2D,0);
            glBindVertexArray(0);
        glUseProgram(0);
    }
}

void GUI_Text::charger()
{
     if(glIsBuffer(mVboID) == GL_TRUE)
        glDeleteBuffers(1,&mVboID);

    glGenBuffers(1,&mVboID);

    glBindBuffer(GL_ARRAY_BUFFER,mVboID);

        glBufferData(GL_ARRAY_BUFFER,mTailleVerticesBytes+mTailleCoordTextureBytes,0,GL_DYNAMIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER,          0          ,mTailleVerticesBytes    , mVertices);
        glBufferSubData(GL_ARRAY_BUFFER,mTailleVerticesBytes ,mTailleCoordTextureBytes, mCoordTexture);

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

void GUI_Text::show(const bool show)
{
    mShow = show;
}

std::string GUI_Text::getText() const
{
    return mText;
}
