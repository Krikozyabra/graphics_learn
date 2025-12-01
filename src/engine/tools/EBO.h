#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO{
    public:
        // Ссылка на элементный буффер
        GLuint ID;
        // Конструктор элементного буффера
        EBO();
        void Init(GLuint* indicies, GLsizeiptr size);
        
        // Подключение элементного буффера к контексту
        void Bind();
        // Отвязка элеметного буффера от контекста
        void Unbind();
        // Удаление элементного буффера
        void Delete();
};

#endif