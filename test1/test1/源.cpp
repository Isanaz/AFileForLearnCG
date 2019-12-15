#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader_s.h"

#include <iostream> 
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// 初始化GLFW
	glfwInit();
	//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //将主版本号设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //将次版本号设为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式
		//（Core-profile）只能使用OpenGL功能的一个子集（不包括我们不需要的向后兼容的特性）

	//创建窗口对象
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);//宽、高、标题、 、 。
	if (window == NULL) {
		cout << "FAIL To Create" << endl;
		glfwTerminate();
		return -1;
	}
	//通知GLFW将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	//对窗口注册一个回调函数：每次窗口大小被调整的时候被调用
		//在创建窗口之后、渲染循环初始化之前注册这些回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD用来管理OpenGL的函数指针，在调用任何OpenGL的函数之前
		//我们需要初始化GLAD
		//glfw的glfwGetProcAddress提供用来加载系统相关的OpenGL函数指针地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//build and compile our shader program编译着色器
	//------------------------------------
	Shader ourShader("shader.vs", "shader.fs");
	//vertex shader
	/*

	int vertexShader = glCreateShader(GL_VERTEX_SHADER); //一个着色器对象，并申明是顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//将这个着色器源码附加到着色器对象上
		   //编译的着色器对象，源码字符串数量，顶点着色器源码，NULL
	glCompileShader(vertexShader);	//编译这段代码
	//check foe shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //检测编译是否成功
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //获取错误信息
		cout << "ERROR:shader:vertex:compilation_failed\n" << infoLog << endl;
	}

	//fragment shader片段着色器：计算像素最后颜色输出
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	//编译过程同上
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR:shader:fragment:compilation_failed\n" << infoLog << endl;
	}

	//link shaders把两个着色器对象连接到一个用来渲染的着色器程序（Shader Program：多个着色器合并并最终链接完成的版本）
		//在渲染对象的时候激活这个着色器程序
		//已激活着色器程序的着色器将在我们发送渲染调用的时候被使用
	int shaderProgram = glCreateProgram();	//创建一个程序对象，返回新创建程序对象的ID引用
	glAttachShader(shaderProgram, vertexShader);	//附加到程序对象上
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);	//将各个着色器相链接
	//check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); //注意与上面检测是否失败的函数不同，上面使用多个是glGetShaderiv
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);	//上面使用的是glGetShaderInfoLog
		cout << "ERROR:shader:program:link_failed\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);	//这两个着色器对象不再需要
	glDeleteShader(fragmentShader);

	*/
	//set up vertex data (and buffer(s)) and configure vertex attributes
	//------------------------------------------------------------------
	float vertices[] = {	//指定三个顶点
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,//R  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,//BL  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,//G  0.0f, 0.0f, 1.0f    // 顶部
	};

	unsigned int indices[] = {
		0, 1, 2,
		//1, 2, 3
	};

	unsigned int VBO, VAO;		//int ???ID号	
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);	//顶点数组对象
	glGenBuffers(1, &VBO); //生成一个缓冲对象，其中1是缓冲ID
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);	//!!!!!!!!先绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //绑定缓冲对象类型（可以绑定多个缓冲，前提是他们是不同的缓冲类型）
				//绑定以后，所使用的任何缓冲调用（在GL_ARRAY_BUFFER目标上的）都会用来配置当前绑定的缓冲（VBO）
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//把用户定义的数据复制到当前绑定缓冲的函数
		//目标缓冲类型，传输数据大小，发送的实际数据，显卡如何管理给定数据（GL_STATIC_DRAW:数据几乎不会改变；GL_DYNAMIC_DRAW:数据会被改变很多；GL_STREAM_DRAW:数据每次绘制都会改变）

	//复制索引数组到索引缓冲
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//告诉OpenGL如何解析顶点数据
				//0：指定要配置的顶点属性。起初在顶点着色器中定义了position顶点属性的位置值为0。
					//而此处希望把数据传递到这个顶点属性中。
				//3：指定顶点属性的大小。vec3由3个值组成
				//GL_FLOAT：指定数据类型（GLSL中vec*都是由浮点数值组成的）
				//GL_FALSE：数据是否被标准化（映射到[0,1]/[-1,1]之间）
				//3*sizeof(float)：步长，在连续的顶点属性组之间的间隔。
				//(void*)0：位置数据在缓冲中起始位置的偏移量。由于参数类型为void*，故需要进行强制类型转化
	glEnableVertexAttribArray(0);

	//颜色属性
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);//启用顶点属性，参数为顶点属性位置（默认禁用）


	// note that this is allowed, the call to glVertexAttribPointer registered VBO 
		// as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);

	//告诉OpenGL渲染窗口（视口Viewport）的尺寸大小
	//glViewport(0, 0, 800, 600);//左下角位置，视口宽度和高度,实际上渲染循环开始已经有了注册函数就可以直接被调了，不必在写出来。

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

		//激活着色器
		//glUseProgram(shaderProgram);
		ourShader.use();

		float timeValue = glfwGetTime();
		float addValue = sin(timeValue) / 2.0f;
		int addLocation = glGetUniformLocation(ourShader.ID, "add");
		glUniform1f(addLocation, addValue);

		glBindVertexArray(VAO);// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//未使用索引： glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//绘制模式，绘制顶点个数，索引类型，偏移量
// glBindVertexArray(0); // no need to unbind it every time 

//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);	//交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲，再这一迭代中被用来绘制，并且将会作为输出显示再屏幕上）
			//双缓冲渲染窗口应用程序。前缓冲保存最终输出的图像，所有的渲染指令再后缓冲上绘制。
			//当渲染指令执行完毕猴，交换前后缓冲，图像立即呈现出来，就不会产生单缓冲的图像闪烁。
		glfwPollEvents();	//检查有没有触发什么事件、更新窗口状态，并调用对应的回调函数
	}

	//optional:de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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
