#include "Shaders.h"

Shader::Shader(): mVertexID(0),mFragmentID(0),mProgramID(0),mVertexSource(),mFragmentSource(0)
{

}

Shader::Shader(std::string vertexSource,std::string fragmentSource): mVertexID(0),mFragmentID(0),mProgramID(0),
                                                                     mVertexSource(vertexSource),mFragmentSource(fragmentSource)
{
    charger();
}

Shader::Shader(Shader const &shaderACopier)
{
    mVertexSource = shaderACopier.mVertexSource;
    mFragmentSource = shaderACopier.mFragmentSource;

    charger();
}

Shader& Shader::operator=(Shader const &shaderACopier)
{
    mVertexSource = shaderACopier.mVertexSource;
    mFragmentSource = shaderACopier.mFragmentSource;

    charger();
    return *this;
}

Shader::~Shader()
{
    glDeleteShader(mVertexID);
    glDeleteShader(mFragmentID);
    glDeleteProgram(mProgramID);
}

GLuint Shader::getProgramID() const
{
    return mProgramID;
}

bool Shader::charger()
{
    if(glIsShader(mVertexID) == GL_FALSE)
        glDeleteShader(mVertexID);

    if(glIsShader(mFragmentID) == GL_FALSE)
        glDeleteShader(mFragmentID);

    if(glIsProgram(mProgramID) == GL_FALSE)
        glDeleteProgram(mProgramID);


    if(!compilerShader(mVertexID,GL_VERTEX_SHADER,mVertexSource))
        return false;

    if(!compilerShader(mFragmentID,GL_FRAGMENT_SHADER,mFragmentSource))
        return false;

    mProgramID = glCreateProgram();

    glAttachShader(mProgramID,mVertexID);
    glAttachShader(mProgramID,mFragmentID);

    glBindAttribLocation(mProgramID,0,"in_Vertex");
    glBindAttribLocation(mProgramID,1,"in_Colors");
    glBindAttribLocation(mProgramID,2,"in_TexCoord0");
    glBindAttribLocation(mProgramID,3,"in_Normals");

    glLinkProgram(mProgramID);

    GLint erreurLink(0);
    glGetProgramiv(mProgramID,GL_LINK_STATUS,&erreurLink);

    if(erreurLink != GL_TRUE)
    {
        GLint tailleErreur(0);
        glGetProgramiv(mProgramID,GL_INFO_LOG_LENGTH,&tailleErreur);

        char *erreur = new char[tailleErreur+1];

        glGetProgramInfoLog(mProgramID,tailleErreur,&tailleErreur,erreur);
        erreur[tailleErreur] = '\0';

        std::cout << erreur << std::endl;

        delete[] erreur;
        glDeleteProgram(mProgramID);

        return false;
    }

    else
        return true;
}

bool Shader::compilerShader(GLuint &shader,GLenum type,std::string &fichierSource)
{
    shader = glCreateShader(type);
    if(shader == 0)
    {
        std::cout << "Erreur le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }

    std::ifstream fichier(fichierSource.c_str());

    if(!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << "n'existe pas" << std::endl;
        glDeleteShader(shader);
        return false;
    }

    /*Stockage des lignes du shader*/

    std::string ligne;
    std::string codeSource;

    while(getline(fichier,ligne))
        codeSource += ligne + '\n';

    fichier.close();

    const GLchar* chaineCodeSource = codeSource.c_str();

    glShaderSource(shader,1,&chaineCodeSource,0);
    glCompileShader(shader);

    GLint erreurCompilation(0);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&erreurCompilation);

    if(erreurCompilation != GL_TRUE)
    {
        GLint tailleErreur(0);
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&tailleErreur);

        char *erreur = new char[tailleErreur + 1];
        glGetShaderInfoLog(shader,tailleErreur,&tailleErreur,erreur);
        erreur[tailleErreur] = '\0';

        std::cout << erreur << std::endl;

        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }

    else
    return true;
}
