#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <iostream>
#include <filesystem>
#include <string>

#include <Quad.h>
#include <Texture.h>
#include <Alienor.h>

void glfw_error_callback(int error_code, const char* error_message); 
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GLAPIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

//be nice when reviewing this code, it was my first crack at programming a full game ;-;
int main()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		std::cout << "[ERROR]GLFW ERROR:: glfw failed to initialize\n";
	} 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Alienor", NULL, NULL);
	glfwSetWindowPos(window, 400, 200);
	if (window == NULL)
	{
		std::cout << "[ERROR]Failed to create GLFW window (glfwCreateWindow)" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL())
	{
		printf("[ERROR] Failed to load modern OpenGL. (gladLoadGL)\n");
		exit(-1);
	}
#ifdef _DEBUG
	std::cout << "OpenGL ";
	std::cout << GLVersion.major;
	std::cout << GLVersion.minor;
	std::cout << '\n';
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_debug_message_callback, (void*)0);
	//glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
#else
	glDisable(GL_DEBUG_OUTPUT);
#endif

	glfwSetKeyCallback(window, glfw_key_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Sage::Alienor alienor_game{};

	glfwSetWindowUserPointer(window, &alienor_game);

	while (!glfwWindowShouldClose(window))
	{
		alienor_game.update(window);
		alienor_game.draw(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void glfw_error_callback(int error_code, const char* error_message)
{
	std::cout << "[ERROR] GLFW ERROR - Error code: " << error_code << "\n|| Error Message: " << error_message << '\n';
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	((Sage::Alienor*)glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
}
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
