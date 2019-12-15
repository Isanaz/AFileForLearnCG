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
	// ��ʼ��GLFW
	glfwInit();
	//����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //�����汾����Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //���ΰ汾����Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ�ú���ģʽ
		//��Core-profile��ֻ��ʹ��OpenGL���ܵ�һ���Ӽ������������ǲ���Ҫ�������ݵ����ԣ�

	//�������ڶ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello", NULL, NULL);//���ߡ����⡢ �� ��
	if (window == NULL) {
		cout << "FAIL To Create" << endl;
		glfwTerminate();
		return -1;
	}
	//֪ͨGLFW�����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	//�Դ���ע��һ���ص�������ÿ�δ��ڴ�С��������ʱ�򱻵���
		//�ڴ�������֮����Ⱦѭ����ʼ��֮ǰע����Щ�ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD��������OpenGL�ĺ���ָ�룬�ڵ����κ�OpenGL�ĺ���֮ǰ
		//������Ҫ��ʼ��GLAD
		//glfw��glfwGetProcAddress�ṩ��������ϵͳ��ص�OpenGL����ָ���ַ
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//build and compile our shader program������ɫ��
	//------------------------------------
	Shader ourShader("shader.vs", "shader.fs");
	//vertex shader
	/*

	int vertexShader = glCreateShader(GL_VERTEX_SHADER); //һ����ɫ�����󣬲������Ƕ�����ɫ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//�������ɫ��Դ�븽�ӵ���ɫ��������
		   //�������ɫ������Դ���ַ���������������ɫ��Դ�룬NULL
	glCompileShader(vertexShader);	//������δ���
	//check foe shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //�������Ƿ�ɹ�
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //��ȡ������Ϣ
		cout << "ERROR:shader:vertex:compilation_failed\n" << infoLog << endl;
	}

	//fragment shaderƬ����ɫ�����������������ɫ���
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	//�������ͬ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR:shader:fragment:compilation_failed\n" << infoLog << endl;
	}

	//link shaders��������ɫ���������ӵ�һ��������Ⱦ����ɫ������Shader Program�������ɫ���ϲ�������������ɵİ汾��
		//����Ⱦ�����ʱ�򼤻������ɫ������
		//�Ѽ�����ɫ���������ɫ���������Ƿ�����Ⱦ���õ�ʱ��ʹ��
	int shaderProgram = glCreateProgram();	//����һ��������󣬷����´�����������ID����
	glAttachShader(shaderProgram, vertexShader);	//���ӵ����������
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);	//��������ɫ��������
	//check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); //ע�����������Ƿ�ʧ�ܵĺ�����ͬ������ʹ�ö����glGetShaderiv
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);	//����ʹ�õ���glGetShaderInfoLog
		cout << "ERROR:shader:program:link_failed\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);	//��������ɫ����������Ҫ
	glDeleteShader(fragmentShader);

	*/
	//set up vertex data (and buffer(s)) and configure vertex attributes
	//------------------------------------------------------------------
	float vertices[] = {	//ָ����������
		// λ��              // ��ɫ
		 0.5f, -0.5f, 0.0f,//R  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,//BL  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,//G  0.0f, 0.0f, 1.0f    // ����
	};

	unsigned int indices[] = {
		0, 1, 2,
		//1, 2, 3
	};

	unsigned int VBO, VAO;		//int ???ID��	
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);	//�����������
	glGenBuffers(1, &VBO); //����һ�������������1�ǻ���ID
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);	//!!!!!!!!�Ȱ�VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //�󶨻���������ͣ����԰󶨶�����壬ǰ���������ǲ�ͬ�Ļ������ͣ�
				//���Ժ���ʹ�õ��κλ�����ã���GL_ARRAY_BUFFERĿ���ϵģ������������õ�ǰ�󶨵Ļ��壨VBO��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���û���������ݸ��Ƶ���ǰ�󶨻���ĺ���
		//Ŀ�껺�����ͣ��������ݴ�С�����͵�ʵ�����ݣ��Կ���ι���������ݣ�GL_STATIC_DRAW:���ݼ�������ı䣻GL_DYNAMIC_DRAW:���ݻᱻ�ı�ܶࣻGL_STREAM_DRAW:����ÿ�λ��ƶ���ı䣩

	//�����������鵽��������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//�趨��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//����OpenGL��ν�����������
				//0��ָ��Ҫ���õĶ������ԡ�����ڶ�����ɫ���ж�����position�������Ե�λ��ֵΪ0��
					//���˴�ϣ�������ݴ��ݵ�������������С�
				//3��ָ���������ԵĴ�С��vec3��3��ֵ���
				//GL_FLOAT��ָ���������ͣ�GLSL��vec*�����ɸ�����ֵ��ɵģ�
				//GL_FALSE�������Ƿ񱻱�׼����ӳ�䵽[0,1]/[-1,1]֮�䣩
				//3*sizeof(float)���������������Ķ���������֮��ļ����
				//(void*)0��λ�������ڻ�������ʼλ�õ�ƫ���������ڲ�������Ϊvoid*������Ҫ����ǿ������ת��
	glEnableVertexAttribArray(0);

	//��ɫ����
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);//���ö������ԣ�����Ϊ��������λ�ã�Ĭ�Ͻ��ã�


	// note that this is allowed, the call to glVertexAttribPointer registered VBO 
		// as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);

	//����OpenGL��Ⱦ���ڣ��ӿ�Viewport���ĳߴ��С
	//glViewport(0, 0, 800, 600);//���½�λ�ã��ӿڿ�Ⱥ͸߶�,ʵ������Ⱦѭ����ʼ�Ѿ�����ע�ắ���Ϳ���ֱ�ӱ����ˣ�������д������

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

		//������ɫ��
		//glUseProgram(shaderProgram);
		ourShader.use();

		float timeValue = glfwGetTime();
		float addValue = sin(timeValue) / 2.0f;
		int addLocation = glGetUniformLocation(ourShader.ID, "add");
		glUniform1f(addLocation, addValue);

		glBindVertexArray(VAO);// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//δʹ�������� glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//����ģʽ�����ƶ���������������ͣ�ƫ����
// glBindVertexArray(0); // no need to unbind it every time 

//��鲢�����¼�����������
		glfwSwapBuffers(window);	//������ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壬����һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϣ�
			//˫������Ⱦ����Ӧ�ó���ǰ���屣�����������ͼ�����е���Ⱦָ���ٺ󻺳��ϻ��ơ�
			//����Ⱦָ��ִ����Ϻ����ǰ�󻺳壬ͼ���������ֳ������Ͳ�������������ͼ����˸��
		glfwPollEvents();	//�����û�д���ʲô�¼������´���״̬�������ö�Ӧ�Ļص�����
	}

	//optional:de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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
