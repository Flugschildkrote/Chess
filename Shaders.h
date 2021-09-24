#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>

class Shader
{
public:
    Shader();
    Shader(std::string vertexSource,std::string fragmentSource);
    Shader(Shader const &shaderACopier);
    Shader& operator=(Shader const &shaderACopier);
    ~Shader();

    GLuint getProgramID() const;
    bool charger();
    bool compilerShader(GLuint &shader,GLenum type,std::string &fichierSource);

private:
    GLuint mVertexID;
    GLuint mFragmentID;
    GLuint mProgramID;
    std::string mVertexSource;
    std::string mFragmentSource;
};

#endif // SHADERS_H_INCLUDED
