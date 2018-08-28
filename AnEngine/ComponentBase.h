#pragma once
#ifndef __COMPONENTBASE_H__
#define __COMPONENTBASE_H__

#include "Object.h"

namespace AnEngine::Game
{
	class ComponentBase : public Object
	{
	public:
		virtual ~ComponentBase() = default;
	};
}
#endif // __COMPONENTBASE_H__
