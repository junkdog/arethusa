#pragma once

#include <bitset>
#include <vector>
#include "World.h"
#include "Constants.h"

// todo: track created vs changedd
// todo: save entities in vector
namespace es {
	class InEditProcessor {

	public:
		InEditProcessor(World& world) : world(world) {}
		virtual ~InEditProcessor() = default;
		EntityEdit& edit();
		void process();

	private:
		EntityBits createdIds;
		EntityBits editedIds;
		vector<Entity> created;
		vector<Entity> changed;
		World world;
	};
}