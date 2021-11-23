#ifndef COLLIDABLE_H_GUARD
#define COLLIDABLE_H_GUARD
#include "Object.h"
#include "Quad.h"
namespace Sage
{
	class Collidable : public Object
	{
	public:
		Collidable(const std::string& name, unsigned int draw_layer)
			:
			Object(name,draw_layer)
		{

		}
		std::pair<bool, Quad*> virtual is_quad() { return std::pair<bool, Quad*>{false, NULL}; }
	};
}
#endif
