#ifndef OBJECT_H_GUARD
#define OBJECT_H_GUARD
#include <string>
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
namespace Sage
{
	class Object
	{
	public:
		const std::string& get_name() const
		{
			return name;
		}
		const unsigned int get_ID() const
		{
			return ID;
		}
		void virtual update(GLFWwindow* window)
		{
			std::cout << "No update function for object with name: " + name + "\nand ID: " + std::to_string(ID);
		}
		void virtual draw(GLFWwindow* window)
		{
			std::cout << "No draw function for object with name: " + name + "\nand ID: " + std::to_string(ID);
		}
	protected:
		Object(const std::string& name)
			:name(name),
			ID(ID_Factory++)
		{

		}
	private:
		inline static unsigned int ID_Factory = 0;
		unsigned int ID;
		std::string name;
	};
}

#endif