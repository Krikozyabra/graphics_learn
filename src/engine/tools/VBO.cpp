#include "VBO.h"

VBO::VBO(){
    // Генерирация контейнера только с 1 объектом
    glGenBuffers(1, &ID);
}

void VBO::Init(GLfloat* vertices, GLsizeiptr size){
    // Указывание VBO как используемого в данном контексте и определение, что он конкретно GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Передача списка вершин в буффер
    // И настройка его как STATIC - один раз определяется, много где используется
    // И как DRAW - для отрисовка
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind(){
    // Указывание VBO как используемого в данном контексте и определение, что он конкретно GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
    // Связывание VBO с 0, чтобы случайно не изменились VBO
    // То есть это эквивалентно unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    // Удаление созданного буффера
    glDeleteBuffers(1, &ID);
}