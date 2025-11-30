#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Object.h"
#include <GLFW/glfw3.h>
#include <cmath>


class Cube : Object{
    private:
        GLfloat size;
        const GLfloat vertices[] = {
            -0.5f, -0.5f * float(sqrt(3)) / 3,      0.0f,   0.8f,   0.3f,   0.02f, // нижний левый угол
            0.5f,  -0.5f * float(sqrt(3)) / 3,      0.0f,   0.8f,   0.3f,   0.02f,// нижний правый уго
            0.0f,   0.5f * float(sqrt(3)) * 2 / 3,  0.0f,   1.0f,   0.6f,   0.32f,// верхний угол
            -0.25f, 0.5f * float(sqrt(3)) / 6,      0.0f,   0.9f,   0.45f,  0.17f,// между 1 и 3
            0.25f,  0.5f * float(sqrt(3)) / 6,      0.0f,   0.9f,   0.45f,  0.17f,// между 2 и 3
            0.0f,  -0.5f * float(sqrt(3)) / 3,      0.0f,   0.8f,   0.3f,   0.02f,// между 2 и 1
        };

    public:
        Cube();
        Cube(GLuint size);

};

#endif