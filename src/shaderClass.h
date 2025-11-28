#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>

std::string get_shader_source(const char* filepath);

class Shader{
    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);

        void Activate();
        void Deactivate();
};

#endif