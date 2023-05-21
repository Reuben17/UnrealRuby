#pragma once
#include "Core.h"

#include "Window.h"
#include "UnrealRuby/LayerStack.h"
#include "UnrealRuby/Events/Event.h"
#include "UnrealRuby/Events/ApplicationEvent.h"


namespace UnrealRuby {
	class UNREALRUBY_API Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		static Application* s_Instance;

	public:
		Application();
		virtual ~Application();

		
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	};

	//To be defined in the client
	Application* CreateApplication();
}

