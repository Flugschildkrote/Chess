#include "Cube.h"

cube::cube(float taille,std::string const vertexShader,std::string const fragmentShader):mShader(vertexShader,fragmentShader),
                                                                                        mVboID(0),mVaoID(0),
                                                                                        mTailleVerticesBytes(108*sizeof(float)),
                                                                                        mTailleCouleursBytes(108*sizeof(float))
{
    mShader.charger();
    taille /= 2;
    float verticesTmp[] = { -taille, -taille, -taille,   taille, -taille,
                            -taille,   taille, taille, -taille, // Face 1
                            -taille, -taille, -taille, -taille, taille,
                            -taille, taille, taille, -taille, // Face 1
                            taille, -taille, taille, taille, -taille,
                            -taille, taille, taille, -taille, // Face 2
                            taille, -taille, taille, taille, taille,
                            taille, taille, taille, -taille, // Face 2
                            -taille, -taille, taille, taille, -taille,
                            taille, taille, -taille, -taille, // Face 3
                            -taille, -taille, taille, -taille, -taille,
                            -taille, taille, -taille, -taille, // Face 3
                            -taille, -taille, taille, taille, -taille,
                            taille, taille, taille, taille, // Face 4
                            -taille, -taille, taille, -taille, taille,
                            taille, taille, taille, taille, // Face 4
                            -taille, -taille, -taille, -taille,
                            -taille, taille, -taille, taille, taille, // Face 5
                            -taille, -taille, -taille, -taille, taille,
                            -taille, -taille, taille, taille, // Face 5
                            -taille, taille, taille, taille, taille,
                            taille, taille, taille, -taille, // Face 6
                            -taille, taille, taille, -taille, taille,
                            -taille, taille, taille, -taille}; // Face 6

    float couleursTmp[] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, // Face 1
                            1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, // Face 1
                            0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, // Face 2
                            0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, // Face 2
                            0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, // Face 3
                            0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, // Face 3
                            1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, // Face 4
                            1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, // Face 4
                            0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, // Face 5
                            0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, // Face 5
                            0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, // Face 6
                            0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0}; // Face 6

                            for(int i(0);i<108;i++)
                            {
                                mVertices[i] = verticesTmp[i];
                                mCouleurs[i] = couleursTmp[i];
                            }
}

cube::~cube()
{
    glDeleteBuffers(1,&mVboID);
    glDeleteVertexArrays(1,&mVaoID);
}

void cube::afficher(glm::mat4 projection,glm::mat4 modelview)
{
    glUseProgram(mShader.getProgramID());
        glBindVertexArray(mVaoID);

            glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"modelview"),1,GL_FALSE,glm::value_ptr(modelview));

            glDrawArrays(GL_TRIANGLES,0,36);

        glBindVertexArray(0);
    glUseProgram(0);
}

void cube::charger()
{
    if(glIsBuffer(mVboID) == GL_TRUE)
        glDeleteBuffers(1,&mVboID);

    glGenBuffers(1,&mVboID);

    if(glIsVertexArray(mVaoID) == GL_TRUE)
        glDeleteVertexArrays(1,&mVaoID);

    glGenVertexArrays(1,&mVaoID);



    glBindBuffer(GL_ARRAY_BUFFER,mVboID);

        glBufferData(GL_ARRAY_BUFFER,mTailleCouleursBytes+mTailleVerticesBytes,0,GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER,0,mTailleVerticesBytes,mVertices);
        glBufferSubData(GL_ARRAY_BUFFER,mTailleVerticesBytes,mTailleCouleursBytes,mCouleurs);

    glBindBuffer(GL_ARRAY_BUFFER,0);


    glBindVertexArray(mVaoID);
        glBindBuffer(GL_ARRAY_BUFFER,mVboID);

            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(mTailleVerticesBytes));
            glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void cube::updateVbo(void *donnees,int tailleBytes,int decalage)
{
    glBindBuffer(GL_ARRAY_BUFFER,mVboID);

    void *adresseVBO = glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);

    if(adresseVBO == NULL)
    {
        std::cout << "Erreur lors de la recuperation du buffer" << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER,0);
        return;
    }

    memcpy((char*)adresseVBO+decalage,donnees,tailleBytes);

    glUnmapBuffer(GL_ARRAY_BUFFER);
    adresseVBO = 0;

    glBindBuffer(GL_ARRAY_BUFFER,0);
}
