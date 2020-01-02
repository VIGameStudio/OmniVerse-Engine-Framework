#pragma once

#include <ove/framework/app.hpp>
#include <ove/core/util/guard.hpp>
#include <ove/system/window.hpp>

#include <string>

namespace ove
{
	namespace framework
	{
		struct engine_t : public core::nocopy
		{
			template <typename TWindow, typename TApp>
			int start(const app_config_t& config)
			{
				return init(new TWindow, config, new TApp);
			}

		private:
			int init(system::window_t* const pWindow, const app_config_t& config, app_t* const pApp);
			void loop(system::window_t* const pWindow, const app_config_t& config, app_t* const pApp);
		};
	}
}