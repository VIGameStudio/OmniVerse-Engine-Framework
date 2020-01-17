#include "engine.hpp"

#include <ove/core/util/thread.hpp>
#include <ove/core/util/time.hpp>

using namespace ove::core;
using namespace ove::system;
using namespace ove::framework;

int engine_t::init(const app_config_t& config, app_t* const pApp)
{
	// Create window.
	if (!config.pWindow->create(config.wconfig))
	{
		std::cerr << "Failed to create window, shutting down ..." << std::endl;
		return EXIT_FAILURE;
	}

	srand((u32)time(NULL));

	// Configure game.
	pApp->config(config);

	// Initialize game.
	if (!pApp->init(config))
	{
		return EXIT_FAILURE;
	}
	
	loop(config, pApp);

	delete config.pRenderDevice;
	delete config.pWindow;

	return EXIT_SUCCESS;
}

void engine_t::loop(const app_config_t& config, app_t* const pApp)
{
#define VERBOSE false
#define LOG_FPS true
#define PROFILE false

	bool looping = true;

	// Create a timer to track the elapsed time
	hres_timer_t frameTimer;
	frameTimer.reset();

	nano_time_t elapsed;
	nano_time_t carry;
	//nano_time_t diff;
	const nano_time_t frameTime = nano_time_t(sec_time_t(1.0 / config.gconfig.target_fps));

	hres_timer_t fpsTimer;
	fpsTimer.reset();

	hres_timer_t profileTimer;
	profileTimer.reset();

	u16 frames = 0;
	const sec_time_t oneSec(1);

	sec_time_t time(0);

	// Start the game loop
	while (looping && !config.pWindow->shouldClose())
	{
		elapsed = frameTimer.elapsed<nano_t>() + carry;
		carry = nano_time_t(0);
		sec_time_t deltaTime = sec_time_t(elapsed);
		time += deltaTime;

		if (PROFILE)
			std::cout << "elapsed: " << deltaTime.count() << "s\n";

		/*if (elapsed < frameTime)
		{
			diff = frameTime - elapsed;

			frameTimer.reset();

			if (VERBOSE)
				std::cout << "sleep: " << sec_time_t(diff).count() << "s\n";
			thread::sleep(diff);

			elapsed = frameTimer.elapsed<nano_t>();
			if (elapsed > diff)
			{
				carry = elapsed - diff;
				if (carry > frameTime)
					carry = frameTime;

				if (VERBOSE)
					std::cout << "carry: " << sec_time_t(carry).count() << "s\n";
			}
		}*/

		frameTimer.reset();

		f64 dt = deltaTime.count();
		dt = dt < 0 ? 0 : dt;

		profileTimer.reset();
		pApp->fixed((f32)time.count(), (f32)dt);
		if (PROFILE)
			std::cout << "fixed: " << profileTimer.secs() << "s\n";

		profileTimer.reset();
		pApp->update((f32)dt);
		if (PROFILE)
			std::cout << "update: " << profileTimer.secs() << "s\n";

		profileTimer.reset();

		pApp->pre_draw();
		pApp->draw();
		pApp->post_draw();

		if (PROFILE)
			std::cout << "render: " << profileTimer.secs() << "s\n";

		config.pWindow->swapBuffers();
		config.pWindow->pollEvents();

		frames++;
		if (fpsTimer.elapsed<sec_t>() >= oneSec)
		{
			if (LOG_FPS)
				std::cout << "FPS: " << frames << "\n";

			fpsTimer.reset();
			frames = 0;
		}
	}

	// Clean resources
	pApp->clean();
}