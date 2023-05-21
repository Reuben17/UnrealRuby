#pragma once

#include "UnrealRuby/Layer.h"

#include "UnrealRuby/Events/ApplicationEvent.h"
#include "UnrealRuby/Events/KeyEvent.h"
#include "UnrealRuby/Events/MouseEvent.h"

namespace UnrealRuby {
	class UNREALRUBY_API ImGuiLayer : public Layer
	{
	private:
		float m_time = 0.0f;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	};
}