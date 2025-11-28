#include "config.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Определение углов треугольника
GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // нижний левый угол
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // нижний правый уго
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // верхний угол
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // между 1 и 3
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // между 2 и 3
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // между 2 и 1
};

GLuint indicies[] = {
    0, 3, 5, // Нижний левый треугольник
    3, 2, 4, // Нижний правый треугольник
    5, 4, 1 // Верхний треугольник
};

int main()
{
    // Инициализация GLFW
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); // <- Устанавливает MSAA x4, это озназачает, что каждый пиксель на экране, будет высчитываться из 4 из буфера. Те буфер должен быть в 4 рааз больше
    // Указание версии GLFW, в моем случае 3.3 и версия OpenGL, в моем случае Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    

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

    Shader myShader("D:\\Projects\\graphics\\src\\shaders\\default.vert",
        "D:\\Projects\\graphics\\src\\shaders\\default.frag");
    
    // Создание и генерация списка вершин
    VAO VAO1;
    VAO1.Bind();

    // Генерация вершинного буфера и привязывает к нему vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Генерация элементного буфера и привязывает к нему indicies
    EBO EBO1(indicies, sizeof(indicies));
    
    // Подвязка VBO к VAO и указание layuout из шейдера
    VAO1.LinkVBO(VBO1, 0);

    // Отвязываем от контекста, чтобы не изменить случайно
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Определение цвета фона окна
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Очистка заднего буффера и назначение нового цвета
    glClear(GL_COLOR_BUFFER_BIT);
    // Смена буффера окна
    glfwSwapBuffers(window);

    // Главный цикл обновления окна, до тех пор пока не будет закрыто
    while(!glfwWindowShouldClose(window))
    {
        // Определение цвета фона окна
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Очистка заднего буффера и назначение нового цвета
        glClear(GL_COLOR_BUFFER_BIT);
        // Указывание OPenGL какую программу хотим использовать
        myShader.Activate();
        // Связывание какой VAO использовать OpenGL
        VAO1.Bind();
        // Отрисовка треугольника используя примитив GL_TRIANGLES
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        // Смена буффера окна, так как у каждого окна есть передний и задний буфер
        /* Логика проста: передний буфер отрисовывается, пока задний подготавливается
        потом они меняются - задний отрисовывается, передний уходит на подготовку*/
        glfwSwapBuffers(window);
        // Функция опрашивающая происходящие ивенты в ОС
        glfwPollEvents();    
    }

    // Удаление созданных буфферов и программ
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    myShader.Deactivate();

    // Уничножение окна
    glfwDestroyWindow(window);
    // Прерываение работы GLFW
    glfwTerminate();
    return 0;
}