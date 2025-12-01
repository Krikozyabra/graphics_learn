#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Cube.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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
    
    Cube *cube1 = new Cube;
    cube1->LoadInMemory();

    GLuint scaleUniId = glGetUniformLocation(myShader.ID, "scale");
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
        cube1->Draw(scaleUniId);
        // Смена буффера окна, так как у каждого окна есть передний и задний буфер
        /* Логика проста: передний буфер отрисовывается, пока задний подготавливается
        потом они меняются - задний отрисовывается, передний уходит на подготовку*/
        glfwSwapBuffers(window);
        // Функция опрашивающая происходящие ивенты в ОС
        glfwPollEvents();    
    }

    // Удаление созданных буфферов и программ
    delete cube1;
    myShader.Deactivate();

    // Уничножение окна
    glfwDestroyWindow(window);
    // Прерываение работы GLFW
    glfwTerminate();
    return 0;
}