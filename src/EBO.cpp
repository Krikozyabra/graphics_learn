#include "EBO.h"

EBO::EBO(GLuint* indicies, GLsizeiptr size){
    // Генерирация контейнера только с 1 объектом
    glGenBuffers(1, &ID);
    // Указывание VBO как используемого в данном контексте и определение, что он конкретно GL_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Передача списка вершин в буффер
    // И настройка его как STATIC - один раз определяется, много где используется
    // И как DRAW - для отрисовка
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
}

void EBO::Bind(){
    // Указывание VBO как используемого в данном контексте и определение, что он конкретно GL_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind(){
    // Связывание VBO с 0, чтобы случайно не изменились VBO
    // То есть это эквивалентно unbind
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete(){
    // Удаление созданного буффера
    glDeleteBuffers(1, &ID);
}