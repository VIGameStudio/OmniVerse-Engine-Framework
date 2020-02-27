#pragma once

#include <iostream>

#include <ove/core/util/guard.hpp>
#include <ove/system/window.hpp>
#include <ove/graphics/renderer/render_device.hpp>

namespace ove
{
	namespace framework
	{
		struct app_config_t
		{
			int argc = 0;
			char** argv = nullptr;
			std::string respath = "";

			system::window_config_t wconfig;
			system::window_t* pWindow = nullptr;

			graphics::render_device_config_t gconfig;
			graphics::render_device_t* pRenderDevice = nullptr;
		};

		struct app_t : public core::nocopy
		{
		public:
			// Returns the specified resources path.
			inline const std::string& getResourcePath() { return m_config.respath; }

			// Returns game window.
			inline system::window_t& getWindow() { return *m_config.pWindow; }

			// Returns game render device.
			inline graphics::render_device_t& getRenderDevice() { return *m_config.pRenderDevice; }

		protected:
			friend struct engine_t;

			// Once at start of program.
			virtual bool init(const app_config_t& config) = 0;

			// Called when app should reset.
			virtual void reset() = 0;

			// Called every poll of input.
			virtual void input() = 0;

			// Called at fixed steps.
			virtual void fixed(core::f32 t, core::f32 dt) = 0;

			// Called every update tick.
			virtual void update(core::f32 dt) = 0;

			// Called once before scene is rendered.
			virtual void pre_draw(core::f32 dt) = 0;

			// Called every draw call for all views.
			virtual void draw(core::f32 dt) = 0;

			// Called once after scene is rendered.
			virtual void post_draw(core::f32 dt) = 0;

			// Called once at end of program.
			virtual void clean() = 0;

		private:
			app_config_t m_config;

			inline void config(const app_config_t& config) { m_config = config; }
		};
	}
}