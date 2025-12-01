#include "Cube.h"

Cube::Cube(){
    this->scale = 1.0f;
    this->VAO1 = new VAO;
    this->VBO1 = new VBO;
    this->EBO1= new EBO;
}

Cube::Cube(GLfloat scale){
    this->scale = scale;
    this->VAO1 = new VAO;
    this->VBO1 = new VBO;
    this->EBO1= new EBO;
}

void Cube::LoadInMemory(){
    // Создание и генерация списка вершин
    VAO1->Bind();
    
    VBO1->Init(vertices, sizeof(vertices));
    EBO1->Init(indicies, sizeof(indicies));
    
    // Подвязка VBO к VAO и указание layuout из шейдера
    VAO1->LinkAttrib(*VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO1->LinkAttrib(*VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    // Отвязываем от контекста, чтобы не изменить случайно
    VAO1->Unbind();
    VBO1->Unbind();
    EBO1->Unbind();
}

void Cube::Draw(GLuint scaleUniId){
    glUniform1f(scaleUniId, scale);
    VAO1->Bind();
    // Отрисовка треугольника используя примитив GL_TRIANGLES
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

Cube::~Cube(){
    VBO1->Delete();
    EBO1->Delete();
    VAO1->Delete();
}