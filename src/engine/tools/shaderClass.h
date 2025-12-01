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
        const static GLuint numOfAttrib = 3*2;
        // Ссылка на шейдерную программу
        GLuint ID;
        // Конструктор шейдерной программы с 2 разными шейдерами
        Shader(const char* vertexFile, const char* fragmentFile);

        // Активация шейдерной программы
        void Activate();
        // Удаление шейдерной программы
        void Deactivate();
};

#endif