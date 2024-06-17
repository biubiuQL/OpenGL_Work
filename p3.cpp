#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Shader.cpp"
#include <string>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
// 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    // unsigned int indices[] = {
    //     // 注意索引从0开始!
    //     // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    //     // 这样可以由下标代表顶点组合成矩形

    //     0, 1, 3, // 第一个三角形
    //     1, 2, 3  // 第二个三角形
    // };

    // 创建顶点缓冲对象
    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // 绑定缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 向缓冲对象中写入数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 配置顶点属性：设置如何读取顶点属性，也就是顶点属性的内存布局
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void *)0);
    // 激活顶点属性数组
    glEnableVertexAttribArray(0);

    // 配置顶点属性：设置如何读取顶点属性，也就是顶点属性的内存布局
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    // 激活顶点属性数组
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma region 着色器加载

    std::string rootPath = "C:\\Users\\admin\\Documents\\OpenGL_Work\\shader\\";
    string vertexPath = rootPath + "Vertex.vs";
    string fragmentPath = rootPath + "Fragment.fs";
    Shader shader(vertexPath.c_str(), fragmentPath.c_str());
    shader.use();

#pragma endregion

    glDrawArrays(GL_TRIANGLES, 0, 6);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        shader.setGlUniform4f("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        // 使用渲染数组
        // glDrawArrays(GL_TRIANGLES, 0, 6);

         glDrawArrays(GL_TRIANGLES, 0, 3);
        // 使用渲染元素
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}