#ifndef _SHADER_H
#define _SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>

#include "Texture.h"

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
    void bindArrayBuffer(GLuint attribLocation, GLuint bufferObject, GLenum type, GLint size, GLsizei stride);
    void use();
    void bindTexture(GLenum, Texture);
    GLint getUniformLocation(std::string);
    GLint getAttribLocation(std::string);
    GLuint getProgramID();
    bool isCompiled();
    std::string getErrorString();

    static Shader loadShaderFromFile(std::string path);
};

#endif