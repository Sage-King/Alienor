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
#include "macro_definitions.h"

void glfw_error_callback(int error_code, const char* error_message); 
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GLAPIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
//taken directly from khronos wiki with minor modifications to filter some messages
{
#ifdef OPEN_GL_FILTERED_DEBUG
	switch (id)
	{
	case 131218:
			break;
	default:
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s, id = %u\n",
				(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
				type, severity, message, id);
	break;
	}
#else
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s, id = %u\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message, id);
#endif
	
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
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Alienor", glfwGetPrimaryMonitor(), NULL);
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

	glfwSetWindowPos(window, 400, 10); 
	std::string icon_filepath = std::filesystem::current_path().string() + "\\resources\\pink_player.png";
	int icon_width, icon_height, icon_color_channels;
	unsigned char* image_data = stbi_load(icon_filepath.c_str(), &icon_width, &icon_height, &icon_color_channels, STBI_rgb_alpha);
	GLFWimage images[1] = { GLFWimage{icon_width, icon_height, image_data} };
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(image_data);

#if _DEBUG & OPEN_GL_VERSION
	std::cout << "OpenGL ";
	std::cout << GLVersion.major;
	std::cout << GLVersion.minor;
	std::cout << '\n';
#endif

#if _DEBUG & OPEN_GL_DEBUG_INFO
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_debug_message_callback, (void*)0);
	glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
#else
	glDisable(GL_DEBUG_OUTPUT);
#endif

	glfwSetKeyCallback(window, glfw_key_callback);
	glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Sage::Alienor alienor_game{window};

	glfwSetWindowUserPointer(window, &alienor_game);

	while (!glfwWindowShouldClose(window))
	{
		alienor_game.update();
		alienor_game.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	if (alienor_game.get_valid_exit())
	{
		glfwTerminate();
		return 0;
	}
	else
	{
		std::cin.get();
		glfwTerminate();
		return 1;
	}
}

void glfw_error_callback(int error_code, const char* error_message)
{
	std::cout << "[ERROR] GLFW ERROR - Error code: " << error_code << "\n|| Error Message: " << error_message << '\n';
}
void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	((Sage::Alienor*)glfwGetWindowUserPointer(window))->mouse_button_callback(window, button, action, mods);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	((Sage::Alienor*)glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
}
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
