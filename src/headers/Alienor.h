#ifndef ALIENOR_H_GUARD
#define ALIENOR_H_GUARD
#include <glm/glm.hpp>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Object.h>
namespace Sage
{
	class Alienor
	{
	public:
		Alienor();

		void update(GLFWwindow* window);
		void draw(GLFWwindow* window);

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		void reg_obj(Object* obj);
	private:
		void process_inputs(GLFWwindow* window);

		double delta_time = 0.0f;
		double last_frame = 0.0f;

		std::vector<std::shared_ptr<Sage::Object>> all_objects;

		glm::vec4 background_color;
	};
}
#endif