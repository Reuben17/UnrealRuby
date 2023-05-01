#include "Application.h"

#include "UnrealRuby/Events/ApplicationEvent.h"
#include "UnrealRuby/Log.h"

namespace UnrealRuby {
	Application::Application()
	{

	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		UR_TRACE(e);

		while (true);
	}
}