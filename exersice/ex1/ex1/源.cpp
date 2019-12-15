#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> 
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//顶点着色器源码
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

//片段着色器源码
const char *fragmentShaderSource1 = "#version 330 core\n"
	"out vec4 FragColor;\n"		//输出变量：vec4类型的FragColor
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"	//R，G，B， alpha(0.0-1.0)
	"}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"		//输出变量：vec4类型的FragColor
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"	//R，G，B， alpha(0.0-1.0)
	"}\n\0";

int main()
{
	// 初始化GLFW
	glfwInit();
	//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式

	//创建窗口对象
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);//宽、高、标题、 、 。
	if (window == NULL) {
		cout << "FAIL To Create" << endl;
		glfwTerminate();
		return -1;
	}
	//通知GLFW将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	//对窗口注册一个回调函数：每次窗口大小被调整的时候被调用在创建窗口之后、渲染循环初始化之前注册这些回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//build and compile our shader program编译着色器
	//------------------------------------
	//vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER); //一个着色器对象，并申明是顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//将这个着色器源码附加到着色器对象上
	glCompileShader(vertexShader);	//编译这段代码
	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //检测编译是否成功
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //获取错误信息
		cout << "ERROR:shader:vertex:compilation_failed\n" << infoLog << endl;
	}

	//fragment shader片段着色器：计算像素最后颜色输出
	int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);	//编译过程同上
	int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader1);
	glCompileShader(fragmentShader2);
	//check for shader compile errors
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		cout << "ERROR:shader:fragment:compilation_failed\n" << infoLog << endl;
	}

	//link shaders
	int shaderProgram1 = glCreateProgram();	
	int shaderProgram2 = glCreateProgram();	
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	//check for linking errors
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success); //注意与上面检测是否失败的函数不同，上面使用多个是glGetShaderiv
	if (!success) {
		glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);	//上面使用的是glGetShaderInfoLog
		cout << "ERROR:shader:program:link_failed\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);	//这两个着色器对象不再需要
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);


	//-----------------------------------------------------------------------------------------------------------------------------------
	//set up vertex data (and buffer(s)) and configure vertex attributes
	//------------------------------------------------------------------
	float tri1[] = {
		//first
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	float tri2[] = {
		//second
		 0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f

	};

	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri1), tri1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//告诉OpenGL如何解析顶点数据
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//告诉OpenGL如何解析顶点数据
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//绘制模式：GL_LINE：线框模式；GL_FILL:填充模式

	//渲染循环（render loop）：再GLFW退出前一直保持运行
	while (!glfwWindowShouldClose(window))	//检查GLFW是否要求被退出
	{
		//输入
		processInput(window); //再每一帧都做出处理 

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数：设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); //状态使用：清空屏幕的颜色缓冲（否则仍能看见上一次迭代的渲染结果）
			//接受一个缓冲位（Buffer Bit）来指定要清空的缓冲：GL_COLOR_BUFFER_BIT/GL_DEPTH_BUFFER_BIT/GL_STENCIL_BUFFER_BIT

		//draw first triangle
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();	//检查有没有触发什么事件、更新窗口状态，并调用对应的回调函数
	}

	//optional:de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	//渲染循环结束，释放/删除之前分配的所有资源
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//arg：一个GLFWwindow，后面两个整数表示窗口新维度
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//检查返回键Esc是否按下，是则关闭GLFW
		glfwSetWindowShouldClose(window, true);
}
