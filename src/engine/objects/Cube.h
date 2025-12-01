#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Object.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <cmath>
#include "shaderClass.h"

class Cube : public Object{
    private:
        VAO *VAO1;
        // Генерация вершинного буфера и привязывает к нему vertices
        VBO *VBO1;
        // Генерация элементного буфера и привязывает к нему indicies
        EBO *EBO1;
        GLfloat scale;
        static const GLuint verticesNum = 8;
        GLfloat vertices[verticesNum*Shader::numOfAttrib] = {
           -0.5f,   -0.5f,      0.0f,   0.8f,   0.3f,   0.02f, //0 нижний левый передний угол
            0.5f,   -0.5f,      0.0f,   0.8f,   0.3f,   0.02f,//1 нижний правый передний угол
            0.5f,    0.5f,      0.0f,   1.0f,   0.6f,   0.32f,//2 верхний правый передний угол
           -0.5f,    0.5f,      0.0f,   1.0f,   0.6f,   0.32f,//3 верхний левый передний угол
           -0.5f,   -0.5f,     -0.5f,   0.8f,   0.3f,   0.02f, //4 нижний левый задний угол
            0.5f,   -0.5f,     -0.5f,   0.8f,   0.3f,   0.02f,//5 нижний правый задний угол
            0.5f,    0.5f,     -0.5f,   1.0f,   0.6f,   0.32f,//6 верхний правый задний угол
           -0.5f,    0.5f,     -0.5f,   1.0f,   0.6f,   0.32f//7 верхний левый задний угол
        };

        GLuint indicies[36] = {
            0, 1, 2,
            2, 3, 1, // передняя стенка
            4, 5, 6,
            6, 7, 4, // задняя стенка
            2, 3, 6,
            6, 7, 3, // верхняя стенка
            0, 1, 4,
            4, 5, 1, // нижняя стенка
            1, 2, 5,
            2, 5, 6, // правая стенка
            0, 3, 4,
            3, 4, 7 // левая стенка
        };

    public:
        Cube();
        Cube(GLfloat scale);
        ~Cube();

        void LoadInMemory() override;
        void Draw(GLuint scaleUniId) override;
};

#endif