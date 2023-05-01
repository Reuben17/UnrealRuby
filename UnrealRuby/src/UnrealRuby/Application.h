#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace UnrealRuby {
	class UNREALRUBY_API Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in the client
	Application* CreateApplication();
}

