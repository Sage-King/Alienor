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
		const unsigned int get_draw_layer() const
		{
			return draw_layer;
		}
		void virtual update(double delta_time)
		{
			std::cout << "No update function for object with name: " + name + "\nand ID: " + std::to_string(ID);
		}
		void virtual draw()
		{
			std::cout << "No draw function for object with name: " + name + "\nand ID: " + std::to_string(ID) + '\n';
		}
	protected:
		Object(const std::string& name, unsigned int draw_layer)
			:name(name),
			ID(ID_Factory++),
			draw_layer(draw_layer)
		{

		}
	private:
		inline static unsigned int ID_Factory = 0;
		unsigned int ID;
		unsigned int draw_layer; //higher layers are drawn over other layers ie. 1 draws over 0, 2 draws over 1, etc. max draw_layer is determined by the Bucket_Vector in Alienor.h
		std::string name;
	};
}
#endif