#include "Obstacle.h"
#include <unordered_map>
#include "Alienor.h"
namespace Sage
{
	Obstacle::Obstacle(const std::string& filepath, int sprite_size_x, int sprite_size_y, double quad_size_x, double quad_size_y, double quad_loc_x, double quad_loc_y)
		:
		Collidable("obstacle_" + std::to_string(ID_factory++) + '_' + filepath.substr(10, filepath.length() - 14)),
		quad(Quad{filepath, sprite_size_x,sprite_size_y, quad_size_x,quad_size_y, quad_loc_x,quad_loc_y })
	{

	}
	void Obstacle::draw()
	{
		quad.draw();
	}
	void Obstacle::update()
	{
	}
}