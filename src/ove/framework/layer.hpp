#pragma once

#include <vector>

#include <ove/core/util/event.hpp>

namespace ove
{
	namespace framework
	{
		struct layer_base_t
		{

		};

		struct layer_mgr_t
		{
		public:
			layer_mgr_t(core::event_bus_t* pEventBus);
			~layer_mgr_t();

			void addLayer(layer_base_t* pLayer);

			void removeLayer(layer_base_t* pLayer);

		private:
			core::event_bus_t* m_pEventBus;

			std::vector<layer_base_t*> m_layers;
		};
	}
}