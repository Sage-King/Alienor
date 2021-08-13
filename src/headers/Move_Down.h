#ifndef MOVE_DOWN_H_GUARD
#define MOVE_DOWN_H_GUARD
#include "Command.h"
namespace Sage
{
	class Move_Down : public Command
	{
	public:
		Move_Down() {}
		~Move_Down() {}
		void execute(const std::shared_ptr<Game_Actor>& actor, double delta_time) override
		{
			actor->move_down(delta_time);
		}
	};
}
#endif