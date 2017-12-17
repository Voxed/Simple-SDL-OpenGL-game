#ifndef _SHADER_H
#define _SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>

class Shader
{
    bool compiled;
    std::string errStr;
    GLuint programID;
    static std::string getShaderLog(GLuint);
    static std::string getProgramLog(GLuint);
public:
    Shader(std::string errStr);
    Shader(GLuint programID);
    Shader();
    GLint getUniformLocation(std::string);
    GLint getAttribLocation(std::string);
    GLuint getProgramID();
    bool isCompiled();
    std::string getErrorString();

    static Shader loadShaderFromFile(std::string path);
};

#endif