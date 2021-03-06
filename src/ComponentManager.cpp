#include "ComponentManager.h"

namespace ecs {

void ComponentManager::clear(const Entity e) {
	auto& components = entityComponentBits[e.id];

	for (auto index : components)
		stores[index]->remove(e);

	components.reset();
}

ComponentBits& ComponentManager::getComponentBits(const Entity e) {
	return entityComponentBits[e.id];
}
}
