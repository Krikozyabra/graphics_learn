#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.h"

class VAO{
    public:
        // Ссылка на вершинный список
        GLuint ID;
        // Конструктор вершинного списка
        VAO();

        // Привзяка VBO к VAO по определнному layout шейдера
        void LinkVBO(VBO VBO, GLuint layout);
        // Привязка вершинного спика к контексту
        void Bind();
        // Отвязка вершинного списка от контекста
        void Unbind();
        // Удаление вершинного списка
        void Delete();
};

#endif