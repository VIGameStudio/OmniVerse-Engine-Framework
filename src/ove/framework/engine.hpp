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
			template <typename TApp>
			inline int start(const app_config_t& config)
			{
				return init(config, new TApp);
			}

		private:
			int init(const app_config_t& config, app_t* const pApp);
			void loop(const app_config_t& config, app_t* const pApp);
		};
	}
}