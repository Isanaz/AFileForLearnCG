#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> 
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//������ɫ��Դ��
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

//Ƭ����ɫ��Դ��
const char *fragmentShaderSource1 = "#version 330 core\n"
	"out vec4 FragColor;\n"		//���������vec4���͵�FragColor
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"	//R��G��B�� alpha(0.0-1.0)
	"}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"		//���������vec4���͵�FragColor
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"	//R��G��B�� alpha(0.0-1.0)
	"}\n\0";

int main()
{
	// ��ʼ��GLFW
	glfwInit();
	//����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ�ú���ģʽ

	//�������ڶ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);//���ߡ����⡢ �� ��
	if (window == NULL) {
		cout << "FAIL To Create" << endl;
		glfwTerminate();
		return -1;
	}
	//֪ͨGLFW�����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	//�Դ���ע��һ���ص�������ÿ�δ��ڴ�С��������ʱ�򱻵����ڴ�������֮����Ⱦѭ����ʼ��֮ǰע����Щ�ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//build and compile our shader program������ɫ��
	//------------------------------------
	//vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER); //һ����ɫ�����󣬲������Ƕ�����ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//�������ɫ��Դ�븽�ӵ���ɫ��������
	glCompileShader(vertexShader);	//������δ���
	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //�������Ƿ�ɹ�
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //��ȡ������Ϣ
		cout << "ERROR:shader:vertex:compilation_failed\n" << infoLog << endl;
	}

	//fragment shaderƬ����ɫ�����������������ɫ���
	int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);	//�������ͬ��
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
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success); //ע�����������Ƿ�ʧ�ܵĺ�����ͬ������ʹ�ö����glGetShaderiv
	if (!success) {
		glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);	//����ʹ�õ���glGetShaderInfoLog
		cout << "ERROR:shader:program:link_failed\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);	//��������ɫ����������Ҫ
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//����OpenGL��ν�����������
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//����OpenGL��ν�����������
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//����ģʽ��GL_LINE���߿�ģʽ��GL_FILL:���ģʽ

	//��Ⱦѭ����render loop������GLFW�˳�ǰһֱ��������
	while (!glfwWindowShouldClose(window))	//���GLFW�Ƿ�Ҫ���˳�
	{
		//����
		processInput(window); //��ÿһ֡���������� 

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//״̬���ú��������������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); //״̬ʹ�ã������Ļ����ɫ���壨�������ܿ�����һ�ε�������Ⱦ�����
			//����һ������λ��Buffer Bit����ָ��Ҫ��յĻ��壺GL_COLOR_BUFFER_BIT/GL_DEPTH_BUFFER_BIT/GL_STENCIL_BUFFER_BIT

		//draw first triangle
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();	//�����û�д���ʲô�¼������´���״̬�������ö�Ӧ�Ļص�����
	}

	//optional:de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	//��Ⱦѭ���������ͷ�/ɾ��֮ǰ�����������Դ
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//arg��һ��GLFWwindow����������������ʾ������ά��
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//��鷵�ؼ�Esc�Ƿ��£�����ر�GLFW
		glfwSetWindowShouldClose(window, true);
}
