#pragma once

#include "System.h"

namespace ecs {

class World;

template<typename Derived>
class EntitySystem : public System, private NoCopy {
  public:
	EntitySystem(World* world, ComponentBits required = {}, ComponentBits disallowed = {})
		: System(world, required, disallowed) {}

	virtual ~EntitySystem() = default;
	virtual void added(__attribute__((__unused__)) const Entity e) {}
	virtual void removed(__attribute__((__unused__)) const Entity e) {}
	virtual void updated(__attribute__((__unused__)) const Entity e) {}

	unsigned int getActiveCount() const {
		return actives.size();
	}

	void processSystem() {
		if (!isActive()) return;

		begin();
		for (const auto entity : actives) {
			static_cast<Derived*>(this)->processEntity(std::move(entity));
		}
		end();
	}
};
}
