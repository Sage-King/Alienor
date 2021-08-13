#ifndef MOVE_RIGHT_H_GUARD
#define MOVE_RIGHT_H_GUARD
#include "Command.h"
namespace Sage
{
	class Move_Right : public Command
	{
	public:
		Move_Right() {}
		~Move_Right() {}
		void execute(const std::shared_ptr<Game_Actor>& actor, double delta_time) override
		{
			actor->move_right(delta_time);
		}
	};
}
#endif