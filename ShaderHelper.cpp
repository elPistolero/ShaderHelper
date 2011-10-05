#include "ShaderHelper.hpp"

// makes a char array from a given file
char* ShaderHelper::readShaderFromFile(const char* fileName) {
    ifstream temp(fileName);
    int count = 0;
    char* buf;

    temp.seekg(0, std::ios::end);
    count = temp.tellg();

    buf = new char[count + 1];
    temp.seekg(0, std::ios::beg);
    temp.read(buf, count);
    buf[count] = 0;
    temp.close();

    return buf;
}

GLint ShaderHelper::compileAndLinkShaders(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile) {
    const char* vertexSrc = readShaderFromFile(vertexShaderFile);
    const char* geomSrc = readShaderFromFile(geometryShaderFile);
    const char* fragSrc = readShaderFromFile(fragmentShaderFile);
    int isCompiledVS, isCompiledGS, isCompiledFS, maxLength, isLinked;
    GLint shader = glCreateProgram();

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**) &vertexSrc, 0);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiledVS);
    if (!isCompiledVS) {
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        char* vertexInfoLog = new char[maxLength];

        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, vertexInfoLog);
        printf("vertex shader: compile error: ");
        printf("%s", vertexInfoLog);
        delete[] vertexInfoLog;
        return;
    }

    // compile the geometry shader
    int geomShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geomShader, 1, (const GLchar**) &geomSrc, 0);
    glCompileShader(geomShader);
    glGetShaderiv(geomShader, GL_COMPILE_STATUS, &isCompiledGS);
    if (!isCompiledGS) {
        glGetShaderiv(geomShader, GL_INFO_LOG_LENGTH, &maxLength);
        char* geomInfoLog = new char[maxLength];

        glGetShaderInfoLog(geomShader, maxLength, &maxLength, geomInfoLog);
        printf("geometry shader: compile error: ");
        printf("%s", geomInfoLog);
        delete[] geomInfoLog;
        return;
    }

    // compile the fragment shader
    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, (const GLchar**) &fragSrc, 0);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiledFS);
    if (!isCompiledFS) {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);
        char* fragInfoLog = new char[maxLength];

        glGetShaderInfoLog(fragShader, maxLength, &maxLength, fragInfoLog);
        printf("fragment shader: compile error: ");
        printf("%s", fragInfoLog);
        delete[] fragInfoLog;
        return;
    }

    // attach and link the shaders to the program
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, geomShader);
    glAttachShader(shader, fragShader);

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, (int*) &isLinked);
    if (!isLinked) {
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];

        glGetProgramInfoLog(shader, maxLength, &maxLength,
                            infoLog);
        fprintf(stdout, "shader: link error: ");
        printf("%s", splattingInfoLog);
        delete[] splattingInfoLog;
        return;
    }

    return shader;
}

GLint ShaderHelper::compileAndLinkShaders(const char* vertexShaderFile, const char* fragmentShaderFile) {
    const char* vertexSrc = readShaderFromFile(vertexShaderFile);
    const char* fragSrc = readShaderFromFile(fragmentShaderFile);
    int isCompiledVS, isCompiledFS, maxLength, isLinked;
    GLint shader = glCreateProgram();

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**) &vertexSrc, 0);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiledVS);
    if (!isCompiledVS) {
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        char* vertexInfoLog = new char[maxLength];

        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, vertexInfoLog);
        printf("vertex shader: compile error: ");
        printf("%s", vertexInfoLog);
        delete[] vertexInfoLog;
        return;
    }

    // compile the fragment shader
    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, (const GLchar**) &fragSrc, 0);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiledFS);
    if (!isCompiledFS) {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);
        char* fragInfoLog = new char[maxLength];

        glGetShaderInfoLog(fragShader, maxLength, &maxLength, fragInfoLog);
        printf("fragment shader: compile error: ");
        printf("%s", fragInfoLog);
        delete[] fragInfoLog;
        return;
    }

    // attach and link the shaders to the program
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragShader);

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, (int*) &isLinked);
    if (!isLinked) {
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];

        glGetProgramInfoLog(shader, maxLength, &maxLength,
                            infoLog);
        fprintf(stdout, "shader: link error: ");
        printf("%s", splattingInfoLog);
        delete[] splattingInfoLog;
        return;
    }

    return shader;
}
