#ifndef SHADERHELPER_H
#define SHADERHELPER_H

#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>

using std::ifstream;

class ShaderHelper {
    public:
        GLint compileAndLinkShaders(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);
        GLint compileAndLinkShaders(const char* vertexShaderFile, const char* fragmentShaderFile);

    private:
        char* readShaderFromFile(const char* fileName);
};

#endif
