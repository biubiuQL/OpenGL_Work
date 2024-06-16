#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ������ɫ��
const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
								   "out vec4 FragColor;\n"
								   "void main()\n"
								   "{\n"
								   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
								   "}\n\0";
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
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f};

	// 创建顶点缓冲对象
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	// 1. 绑定VAO
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	// 绑定缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 向缓冲对象中写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 配置顶点属性：设置如何读取顶点属性，也就是顶点属性的内存布局
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void *)0);
	// 激活顶点属性数组
	glEnableVertexAttribArray(0);

	// ·······················着色器编译····························

	// -----------顶点着色器编译
	// 创建顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 读取顶点着色器源代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// 编译顶点着色器
	glCompileShader(vertexShader);
	// 检查编译结果
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// ---顶点着色器编译end

	// ---片段着色器编译
	// 创建片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 读取片段着色器源代码
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译片段着色器
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	// ---片段着色器编译end
	// ·······················着色器编译end

	// ·······················创建着色器程序·····················

	// 创建着色器程序
	unsigned int shaderProgram = glCreateProgram();
	// 附加顶点着色器
	glAttachShader(shaderProgram, vertexShader);
	// 附加片段着色器
	glAttachShader(shaderProgram, fragmentShader);
	// 链接着色器程序
	glLinkProgram(shaderProgram);
	// 检查链接结果
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				  << infoLog << std::endl;
	}
	// 使用着色器程序
	glUseProgram(shaderProgram);
	// ·······················创建着色器程序end
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
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