#ifndef INPUT_HANDLER_H_GUARD
#define INPUT_HANDLER_H_GUARD
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Command_Include_list.h"
namespace Sage
{
	class Input_Handler
	{
	public:
		Input_Handler(GLFWwindow* window)
			:window_pointer(window)
		{

		}
		std::vector<Command*> retrieve_input()
		{
			std::vector<Command*> ret_vector;
			if (is_pressed(GLFW_KEY_W)) ret_vector.push_back(&w_command);
			if (is_pressed(GLFW_KEY_A)) ret_vector.push_back(&a_command);
			if (is_pressed(GLFW_KEY_S)) ret_vector.push_back(&s_command);
			if (is_pressed(GLFW_KEY_D)) ret_vector.push_back(&d_command);
			return ret_vector;
		}
	private:
		inline bool is_pressed(int glfw_key)
		{
			if (glfwGetKey(window_pointer, glfw_key) == GLFW_PRESS)
				return true;
			return false;
		}

		GLFWwindow* window_pointer;

		Move_Up w_command;
		Move_Left a_command;
		Move_Down s_command;
		Move_Right d_command;
		
	};
}
#endif