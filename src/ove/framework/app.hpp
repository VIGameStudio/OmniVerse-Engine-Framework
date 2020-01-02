#pragma once

#include <iostream>

#include <ove/system/window.hpp>
#include <ove/core/util/guard.hpp>

namespace ove
{
	namespace framework
	{
		struct app_config_t
		{
			std::string respath = "";
			system::window_config_t wconfig;
			core::u32 target_fps = 0;
		};


		struct app_t : public core::nocopy
		{
		public:
			app_t() : m_pWindow(nullptr) {}
			~app_t() {}

		private:
			// Game window
			system::window_t* m_pWindow;

			friend struct engine_t;
			inline void config(system::window_t* pWindow) { m_pWindow = pWindow; }

		protected:
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
			virtual void pre_draw() = 0;

			// Called every draw call for all views.
			virtual void draw() = 0;

			// Called once after scene is rendered.
			virtual void post_draw() = 0;

			// Called once at end of program.
			virtual void clean() = 0;

			// Returns game window.
			inline system::window_t const & getWindow() { return *m_pWindow; }
		};
	}
}