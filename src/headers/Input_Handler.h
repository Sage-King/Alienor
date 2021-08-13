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
		std::vector<Command*> handle_input()
		{
			std::vector<Command*> ret_vector;
			if (is_pressed(GLFW_KEY_I)) ret_vector.push_back(&i_command);
			if (is_pressed(GLFW_KEY_J)) ret_vector.push_back(&j_command);
			if (is_pressed(GLFW_KEY_K)) ret_vector.push_back(&k_command);
			if (is_pressed(GLFW_KEY_L)) ret_vector.push_back(&l_command);
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

		Move_Up i_command;
		Move_Left j_command;
		Move_Down k_command;
		Move_Right l_command;
		
	};
}
#endif