#include "Booster.h"
#include <unordered_map>
#include "Alienor.h"

namespace Sage
{
	Booster::Booster(const std::string& filepath, unsigned int sprite_size_x, unsigned int sprite_size_y, double quad_size_x, double quad_size_y, double quad_loc_x, double quad_loc_y, unsigned int draw_layer)
		:
		Collidable("booster_" + std::to_string(ID_factory++) + '_' + filepath.substr(10, filepath.length() - 14), draw_layer),
		quad(Quad{ filepath, sprite_size_x,sprite_size_y, quad_size_x,quad_size_y, quad_loc_x,quad_loc_y })
	{

	}
	Booster::Booster(double quad_loc_x, double quad_loc_y, double quad_size_x, double quad_size_y, unsigned int draw_layer)
		:
		Collidable("booster_" + std::to_string(ID_factory++), draw_layer),
		quad(Quad{ glm::vec4{0.0,0.0,1.0,1.0}, quad_size_x, quad_size_y, quad_loc_x, quad_loc_y })
	{

	}
	void Booster::draw()
	{
		quad.draw();
	}
	void Booster::update(double delta_time)
	{
		quad.y += 0.5f * delta_time;
		if (quad.y >= 1.0f)
		{
			marked_for_death = true;
		}
	}
}