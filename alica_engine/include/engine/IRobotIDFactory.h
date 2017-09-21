#pragma once

#include <engine/IRobotID.h>

namespace alica{

	class IRobotIDFactory
	{
	public:
		virtual ~IRobotIDFactory() {};
		virtual IRobotID create(uint8_t* idBytes, int idSize) const = 0;

	};

}