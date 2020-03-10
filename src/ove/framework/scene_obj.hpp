#pragma once

#include <ove/ecs/entity.hpp>
#include <ove/core/container/tree.hpp>

namespace ove
{
	namespace framework
	{
		struct scene_obj_t
		{
		public:
			inline ecs::entity_t& getEntity() { return m_entity; }

			inline core::tree_node_t<scene_obj_t>& getNode() { return m_node; }

		private:
			ecs::entity_t m_entity;
			core::tree_node_t<scene_obj_t> m_node;
		};
	}
}