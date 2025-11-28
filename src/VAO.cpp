#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO VBO, GLuint layout){
    VBO.Bind();
    // Настройка Vertex Attribute, чтобы указать OpenGL как читать VBO
    // index - с какого начать считывать
    // size - сколько вершин
    // type - тип данных в VBO
    // normalized - хз
    // stride - сколько данных отводится на 1 вершину
    // pointer - указатель на пустоту))
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    // Активация VertexAttribute, чтобы OpenGL понимал, что его нужно использовать
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind(){
    glBindVertexArray(ID);
}

void VAO::Unbind(){
    // Связывание VAO с 0, чтобы случайно не изменились VAO
    // То есть это эквивалентно unbind
    glBindVertexArray(0);
}

void VAO::Delete(){
    // Удаление созданного списка
    glDeleteVertexArrays(1, &ID);
}