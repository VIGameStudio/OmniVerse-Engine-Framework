#pragma once

#include <ove/framework/app.hpp>

namespace ove
{
	namespace framework
	{
		struct game_t
		{
		public:
			game_t(ove::framework::app_t& app)
				: m_window(app.getWindow())
				, m_renderDevice(app.getRenderDevice())
			{}

			virtual void init() = 0;
			virtual void update(ove::core::f32 dt) = 0;
			virtual void draw(ove::core::f32 dt) = 0;
			virtual void clean() = 0;

		protected:
			ove::system::window_t& m_window;
			ove::graphics::render_device_t& m_renderDevice;
		};
	}
}