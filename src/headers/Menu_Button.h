#ifndef MENU_BUTTON_H_GUARD
#define MENU_BUTTON_H_GUARD

#include "Object.h"
#include "Quad.h"
#include <functional>

namespace Sage
{
	class Menu_Button : public Object
	{
	public:
		Menu_Button(const std::string& name, unsigned int draw_layer, const std::string& filepath, unsigned int size_of_sprite_x_in_px, unsigned int size_of_sprite_y_in_px, double width, double height, double in_x, double in_y, std::function<void()> button_function)
			:
			Object(name, draw_layer),
			quad(filepath, size_of_sprite_x_in_px, size_of_sprite_y_in_px, width, height, in_x, in_y),
			button_function(button_function) {}
		~Menu_Button() {}

		void draw() override
		{
			quad.draw();
		}

		void execute() { button_function(); }
		Quad* get_quad() { return &quad; }
	private:
		std::function<void()> button_function;
		Quad quad;
	};
}
#endif