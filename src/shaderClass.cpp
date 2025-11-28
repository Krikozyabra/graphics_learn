#include "shaderClass.h"

// Функция, которая считывает исходный код шейдеров
std::string get_shader_source(const char* filepath){
    std::ifstream sfile(filepath);
    if(sfile){
        std::stringstream sbuffer;
        sbuffer << sfile.rdbuf();
        sfile.close();
        return sbuffer.str();
    }
    throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){
    std::string vertexCode = get_shader_source(vertexFile);
    std::string fragmentCode = get_shader_source(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Создание объекта шейдера и получение ссылки на него
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Указывание исходного кода шейдера
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Компиляция шейдера в машинный код
    glCompileShader(vertexShader);

    // Переменные для записи информации о компиляции шейдеров
    int success;
    char infoLog[512];

    // Получение статуса компиляции шейдера
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        // Получение сообщения, если шейдер не успешно скомпилировался
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader error:\n" << infoLog << std::endl;
    }

    // Подготовка шейдера фрагментов по аналогии с вершинным
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader error:\n" << infoLog << std::endl;
    }

    // Создание программы, которая будет работать с шейдерами
    ID = glCreateProgram();
    // Связывание шейдеров с программой
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Объединение привязанных шейдеров воедино внутри программы
    glLinkProgram(ID);

    // Очищение памяти, так как эти шейдеры уже внутри программы
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Deactivate(){
    glDeleteProgram(ID);
}