#include <algorithm>
#include "Constants.h"
#include "Entity.h"
#include "System.h"
#include "ComponentManager.h"
#include "World.h"

namespace ecs {

	ComponentBits System::requiredAspect() {
		return ComponentBits();
	}

	ComponentBits System::disallowedAspect() {
		return ComponentBits();
	}

	void System::initialize() {}

	void System::insert(std::vector<Entity>& entities) {
		for (auto e : entities)
			insert(e);
	}

	void System::insert(Entity e) {
		if (isInterested(e) && !activeIds[e.id]) {
			activeIds[e.id] = true;
			this->added(e);

			activeNeedsRebuilding = true;
		}
	}

	void System::remove(std::vector<Entity>& entities) {
		for (auto e : entities)
			remove(e);
	}

	void System::remove(Entity e) {
		if (activeIds[e.id]) {
			activeIds[e.id] = false;
			this->removed(e);

			activeNeedsRebuilding = true;
		}
	}


	void System::update(std::vector<Entity>& entities) {
		for (auto e : entities)
			update(e);
	}

	void System::update(Entity e) {
		bool interested = isInterested(e);
		bool inSystem = activeIds[e.id];

		if (interested && !inSystem) {
			insert(e);
		} else if (interested && inSystem) {
			updated(e);
		} else if (!interested && inSystem) {
			remove(e);
		}
	}

	void System::syncActiveEntities() {
		if (activeNeedsRebuilding) {
			activeNeedsRebuilding = false;
			syncEntities(activeIds, actives);
		}
	}

	bool System::isActive() {
		return isVoidSystem || !actives.empty();
	}

	bool System::isInterested(Entity e) {
		if (isVoidSystem) return false;

		auto& componentBits = world->components().getComponentBits(e);
		if (requiredComponents != logicalAND(componentBits, requiredComponents))
			return false;

		if (logicalAND(componentBits, disallowedComponents).any())
			return false;

		return true;
	}

	ComponentBits& System::logicalAND(ComponentBits a, ComponentBits b) {
		tmpBits.reset();
		tmpBits |= a;
		tmpBits &= b;
		return tmpBits;
	}
}
