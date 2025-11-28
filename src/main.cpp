#include "config.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

string get_shader_source(const char* filepath){
    ifstream sfile(filepath);
    if(!sfile.is_open()){
        cerr << "Error opening file: " << filepath << endl;
        return 0;
    }
    stringstream sbuffer;
    sbuffer << sfile.rdbuf();
    return sbuffer.str();
}

int main()
{
    // Инициализация GLFW
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }


    // glfwWindowHint(GLFW_SAMPLES, 4); <- Устанавливает MSAA x4, это озназачает, что каждый пиксель на экране, будет высчитываться из 4 из буфера. Те буфер должен быть в 4 рааз больше
    // Указание версии GLFW, в моем случае 3.3 и версия OpenGL, в моем случае Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) / 3, 0.0f
    };

    //Создание окна, первый NULL отвечает за конфигурацию монитора, второй за наличие родителя, например, какое-то первое окно
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "ZMMR", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window"  << endl;
        return -1;
    }
    // Указание конкста для текущего поток
    // Те все изменения буферов, пикслей и тд внутри этого потока, будут применяться к выбранному окну
    glfwMakeContextCurrent(window);

    // Инициализация GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    // Определение размера кадрого буфера
    glViewport(0, 0, 800, 600);
    // Создание callback на изменение размера окна, чтобы потом изменить размер буфера
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Считываем код шейдера вершин
    string vss = get_shader_source("D:/Projects/graphics/src/shaders/default.vert");
    const char* vssource_c_str = vss.c_str();
    // Создание объекта шейдера
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Указание исходного кода шейдера
    glShaderSource(vertexShader, 1, &vssource_c_str, NULL);
    // Компиляция шейдера
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Vertex shader error:\n" << infoLog << endl;
    }

    // Считываем код шейдера фрагментов
    string fss = get_shader_source("D:/Projects/graphics/src/shaders/default.frag");
    const char* fssource_c_str = fss.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fssource_c_str, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "Fragment shader error:\n" << infoLog << endl;
    }

    // Создание программы, которая будет работать с шейдерами
    GLuint shaderProgram = glCreateProgram();
    // Связка шейдеров с программой
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Привязка программы к окну
    glLinkProgram(shaderProgram);

    // Очищаем память, так как эти шейдеры уже внутри программы
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Определяем цвет фона окна
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Очищаем задний буффер и назначаем новые цвета
    glClear(GL_COLOR_BUFFER_BIT);
    // Меняем буфферы окна
    glfwSwapBuffers(window);

    // Главный цикл обновления окна, до тех пор пока не будет закрыто
    while(!glfwWindowShouldClose(window))
    {
        // Определяем цвет фона окна
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Очищаем задний буффер и назначаем новые цвета
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Меняем буфферы окна, так как у каждого окна есть передний и задний буфер
        /* Логика проста: передний буфер отрисовывается, пока задний подготавливается
        потом они меняются - задний отрисовывается, передний уходит на подготовку*/
        glfwSwapBuffers(window);
        // Функция опрашивающая происходящие ивенты в ОС
        glfwPollEvents();    
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Уничножение окна
    glfwDestroyWindow(window);
    // Прерываение работы GLFW
    glfwTerminate();
    return 0;
}