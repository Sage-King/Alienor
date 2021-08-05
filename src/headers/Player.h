#ifndef PLAYER_H_GUARD
#define PLAYER_H_GUARD
#include "Object.h"
#include "Alienor.h"
namespace Sage
{
	class Player : public Object
	{
	public:
		Player();
		~Player();

		void draw(GLFWwindow* window) override;
		void update(GLFWwindow* window) override;
	};
}
#endif