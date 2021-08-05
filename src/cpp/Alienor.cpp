#include "Alienor.h"

#include "Texture.h"
#include "Quad.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Player.h"
namespace Sage
{
	Alienor::Alienor()
		:
		background_color(glm::vec4(0.0f,0.1f,0.1f,1.0f))
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Sage::Player main_player{};
		reg_obj(&main_player);
	}

	void Alienor::update(GLFWwindow* window)
	{
		process_inputs(window);
		double current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		for (int i = 0; i < all_objects.size(); i++)
		{
			all_objects[i]->update(window);
		}
	}
	void Alienor::draw(GLFWwindow* window)
	{
		glClearColor(background_color.x, background_color.y, background_color.z, background_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		for (int i = 0; i < all_objects.size(); i++)
		{
			all_objects[i]->draw(window);
		}
	}

	void Alienor::process_inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
			((Sage::Quad*)glfwGetWindowUserPointer(window))->x -= (float)(1.0 * delta_time);
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
			((Sage::Quad*)glfwGetWindowUserPointer(window))->x += (float)(1.0 * delta_time);
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
			((Sage::Quad*)glfwGetWindowUserPointer(window))->y -= (float)(1.0 * delta_time);
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			((Sage::Quad*)glfwGetWindowUserPointer(window))->y += (float)(1.0 * delta_time);
	}

	void Alienor::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}


	void Alienor::reg_obj(Object* obj)
	{
		for (int i = 0; i < all_objects.size(); i++)
		{
			if (obj->get_name() == all_objects[i]->get_name())
			{
				std::cout << "Name conflict: " + obj->get_name() + " between object: " + std::to_string(obj->get_ID()) + " and object: " + std::to_string(all_objects[i]->get_ID()) + '\n';
				return;
			}
		}
		all_objects.push_back(std::shared_ptr<Object>{obj});
	}
}
