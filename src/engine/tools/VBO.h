#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO{
    public:
        // Ссылка вершинного буффера
        GLuint ID;
        // Конструктор вершинного буффера и привязка к нему verticies
        VBO(GLfloat* vertices, GLsizeiptr size);
        
        // Привязка вершинного буффера к контексту
        void Bind();
        // Отвязка вершинного буффера от контекста
        void Unbind();
        // Удаление вершинного буффера
        void Delete();
};

#endif