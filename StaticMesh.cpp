#include "StaticMesh.h"

Mesh::Mesh(std::string name,float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture,std::string const modele3D):mShader(vertexShader,fragmentShader),
                                                                                        mVboID(0),mVaoID(0),mTexture(texture),
                                                                                        mTailleVerticesBytes(0), mTailleCoordTextureBytes(0),mTailleNormalsBytes(0),
                                                                                        decoder(modele3D),mNbVertices(0),mNbAnimations(0),mPosition(0,0,0),mScale(taille,taille,taille),mAmbiantIntensity(0.8),mObjFile(modele3D),mName(name)
{
    mTexture.load();
   // std::cout << "ok" << std::endl;
    decoder.lireFichier();
    mNbAnimations = decoder.getNombreAnims();
    OBJDecoder animDecoder(mObjFile);
    modelview = glm::mat4(1.0);

    //std::cout << mNbAnimations << std::endl;
    for(int i(0); i < mNbAnimations; i++)
    {
        std::vector<std::vector<float> > animArray;
        animArray = animDecoder.getAnimation(i);
        Animation animTmp(animArray);
        mMeshAnims.push_back(animTmp);
    }
    /**//**//*Initialiser les anims*/
    std::vector<float> vertTemps = decoder.getVertices();
    std::vector<float> textTmp = decoder.getCoordTexture();
    std::vector<float> normalsTmp = decoder.getNormals();

    mVerticesBis = vertTemps;
    mNbVertices = (int) vertTemps.size()/3;

    mTailleVerticesBytes = (int) vertTemps.size()*sizeof(float);
    mTailleCoordTextureBytes = (int) textTmp.size()*sizeof(float);
    mTailleNormalsBytes = (int) normalsTmp.size()*sizeof(float);


    for(int i(0);i<vertTemps.size();i++)
    {
        mVertices[i] = vertTemps[i];
    }
    for(int i(0);i < textTmp.size(); i++)
    {
        mCoordTexture[i] = textTmp[i];
    }
    for(int i(0); i < normalsTmp.size(); i++)
    {
        mNormals[i] = normalsTmp[i];
    }
}

Mesh::Mesh(const Mesh &meshACopier) : mShader(meshACopier.mShader),mVboID(meshACopier.mVboID),mVaoID(meshACopier.mVaoID),
                                 mTexture(meshACopier.mTexture),mTailleVerticesBytes(meshACopier.mTailleVerticesBytes),
                                 mTailleCoordTextureBytes(meshACopier.mTailleCoordTextureBytes),mTailleNormalsBytes(meshACopier.mTailleNormalsBytes),
                                 decoder(meshACopier.mObjFile),mNbVertices(meshACopier.mNbVertices),mNbAnimations(meshACopier.mNbAnimations),mPosition(meshACopier.mPosition),mScale(meshACopier.mScale),mAmbiantIntensity(meshACopier.mAmbiantIntensity),
                                 mObjFile(meshACopier.mObjFile),mName(meshACopier.mName),modelview(meshACopier.modelview),mMeshAnims(meshACopier.mMeshAnims),hitBox(meshACopier.hitBox)
{
    mTexture.load();
   // std::cout << "ok" << std::endl;
    decoder.lireFichier();
    mNbAnimations = decoder.getNombreAnims();
    OBJDecoder animDecoder(mObjFile);
    modelview = glm::mat4(1.0);

    //std::cout << mNbAnimations << std::endl;
    for(int i(0); i < mNbAnimations; i++)
    {
        std::vector<std::vector<float> > animArray;
        animArray = animDecoder.getAnimation(i);
        Animation animTmp(animArray);
        mMeshAnims.push_back(animTmp);
    }
    /**//**//*Initialiser les anims*/
    std::vector<float> vertTemps = decoder.getVertices();
    std::vector<float> textTmp = decoder.getCoordTexture();
    std::vector<float> normalsTmp = decoder.getNormals();

    mVerticesBis = vertTemps;
    mNbVertices = (int) vertTemps.size()/3;

    mTailleVerticesBytes = (int) vertTemps.size()*sizeof(float);
    mTailleCoordTextureBytes = (int) textTmp.size()*sizeof(float);
    mTailleNormalsBytes = (int) normalsTmp.size()*sizeof(float);


    for(int i(0);i<vertTemps.size();i++)
    {
        mVertices[i] = vertTemps[i];
    }
    for(int i(0);i < textTmp.size(); i++)
    {
        mCoordTexture[i] = textTmp[i];
    }
    for(int i(0); i < normalsTmp.size(); i++)
    {
        mNormals[i] = normalsTmp[i];
    }
}

Mesh::~Mesh()
{
    glDeleteBuffers(1,&mVboID);
    glDeleteVertexArrays(1,&mVaoID);
}

void Mesh::afficher(glm::mat4 projection, glm::mat4 view)
{
    glUseProgram(mShader.getProgramID());
        glBindVertexArray(mVaoID);

            glm::mat4 save = modelview;
            if(mScale != glm::vec3(1.0,1.0,1.0));
                modelview = glm::scale(modelview,mScale);
            glm::mat4 normalsMatrix = glm::transpose(glm::inverse(modelview));
            glm::mat4 modelviewProjection = projection*view*modelview;
            modelview = save;

            glm::vec3 lightDirection(0,-1,0);
            glm::vec3 lightColor(1,1,1);
            float lightIntensity = 0.7;
            //glm::vec3 ambiantLightColor;
            //float ambiantLightIntensity = 0.2;
           // ambiantLightColor.x = 1;
           // ambiantLightColor.y = 1;
           // ambiantLightColor.z = 1;
                glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"projection"), 1, GL_FALSE, glm::value_ptr(projection));
                glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"view"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"modelviewProjection"), 1, GL_FALSE, glm::value_ptr(modelviewProjection));
                glUniformMatrix4fv(glGetUniformLocation(mShader.getProgramID(),"normalsMatrix"), 1, GL_FALSE, glm::value_ptr(normalsMatrix));
                glUniform1f(glGetUniformLocation(mShader.getProgramID(),"sun.ambiantIntensity"),lightIntensity);
                glUniform3f(glGetUniformLocation(mShader.getProgramID(),"sun.direction"),lightDirection.x,lightDirection.y,lightDirection.z);
                glUniform3f(glGetUniformLocation(mShader.getProgramID(),"sun.color"),lightColor.x,lightColor.y,lightColor.z);
                glUniform1f(glGetUniformLocation(mShader.getProgramID(),"modelIntensity"),mAmbiantIntensity);
               // glUniform3f(glGetUniformLocation(mShader.getProgramID(),"ambiantLightColor"),ambiantLightColor.x,ambiantLightColor.y,ambiantLightColor.z);
               // glUniform1f(glGetUniformLocation(mShader.getProgramID(),"ambiantIntensity"),ambiantLightIntensity);

                glBindTexture(GL_TEXTURE_2D,mTexture.getID());

                glDrawArrays(GL_TRIANGLES,0,mNbVertices);

            glBindTexture(GL_TEXTURE_2D,0);
        glBindVertexArray(0);
    glUseProgram(0);
}

void Mesh::updateVbo(void *donnees,int tailleBytes,int decalage)
{
    glBindBuffer(GL_ARRAY_BUFFER,mVboID);

    void *adresseVBO = glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);

    if(adresseVBO == NULL)
    {
        std::cout << "Erreur lors de la recuperation du buffer" << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER,0);
        return;
    }

    mVertices[5] = 0;
    mVertices[20] = 200;
    memcpy((char*)adresseVBO+decalage,donnees,tailleBytes);

    glUnmapBuffer(GL_ARRAY_BUFFER);
    adresseVBO = 0;

    glBindBuffer(GL_ARRAY_BUFFER,0);
}


void Mesh::charger()
{
    if(glIsBuffer(mVboID) == GL_TRUE)
        glDeleteBuffers(1,&mVboID);

    glGenBuffers(1,&mVboID);

    glBindBuffer(GL_ARRAY_BUFFER,mVboID);

        glBufferData(GL_ARRAY_BUFFER,mTailleVerticesBytes+mTailleCoordTextureBytes+mTailleVerticesBytes,0,GL_DYNAMIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER,          0                                  ,mTailleVerticesBytes    ,mVertices);
        glBufferSubData(GL_ARRAY_BUFFER,mTailleVerticesBytes                         ,mTailleCoordTextureBytes,mCoordTexture);
        glBufferSubData(GL_ARRAY_BUFFER,mTailleVerticesBytes+mTailleCoordTextureBytes,mTailleNormalsBytes     ,mNormals);

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

            glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(mTailleVerticesBytes+mTailleCoordTextureBytes));
            glEnableVertexAttribArray(3);

        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Mesh::addCollider3D(std::string colliderName,std::string forme, glm::vec3 taille, glm::vec3 decalage)
{
    hitBox.push_back(Collider3D(colliderName,forme,mPosition,taille,decalage));
}

bool Mesh::checkRayCollision(glm::vec3 rayStart, glm::vec3 rayEnd, int hitBoxID)
{
    return hitBox[hitBoxID].checkRayCollision(rayStart,rayEnd);
}

void Mesh::actualizeColliderPosition(int hitBoxID)
{
    hitBox[hitBoxID].actualizePosition(mPosition);
}

void Mesh::translate(const glm::vec3 translation)
{
    modelview = glm::translate(modelview,translation);
    mPosition += translation;
}

void Mesh::rotate(const float angle, const glm::vec3 axe)
{
    modelview = glm::rotate(modelview,angle,axe);
}

void Mesh::scale(const glm::vec3 scale)
{
    mScale = scale;
}

void Mesh::setPosition(const glm::vec3 newPosition)
{
    glm::vec3 translation = newPosition-mPosition;
    modelview = glm::translate(modelview,translation);
    mPosition = newPosition;
}

void Mesh::setName(const std::string newName)
{
    mName = newName;
}

void Mesh::setAmbiantIntensity(const float intensity)
{
    mAmbiantIntensity = intensity;
}

void Mesh::setTexture(const std::string newTexture)
{
    mTexture = Texture(newTexture);
    mTexture.load();
}

glm::vec3 Mesh::getPosition() const
{
    return mPosition;
}

glm::vec3 Mesh::getColliderPosition(const int colliderID) const
{
    return hitBox[colliderID].getPosition();
}

bool Mesh::PlayAnim(int animation, int repetition)
{
    if(animation >= mNbAnimations)
        std::cout << "L'animation " << animation << " n'existe pas." << std::endl;
    else
    {
        std::vector<float> vectorFrame = mMeshAnims[animation].Play(repetition);
        if(vectorFrame.size() != 0)
        {
            updateVbo(vectorFrame.data(),mTailleVerticesBytes,0);
        }
        else
        {
           return false;
        }
    }
    return true;
}

std::vector<float> Mesh::getVertices() const
{
    std::vector<float> vert = mVerticesBis;
    return vert;
}

glm::vec3 Mesh::getHitRayPosition(int hitBoxID) const
{
    return hitBox[hitBoxID].getHitRayPosition();
}

Collider3D Mesh::getCollider(int colliderID) const
{
    return hitBox[colliderID];
}

int Mesh::getNombreCollider() const
{
    return hitBox.size();
}

std::string Mesh::getName() const
{
    return mName;
}
