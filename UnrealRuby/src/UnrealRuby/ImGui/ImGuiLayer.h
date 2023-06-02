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
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		//void SetDarkThemeColors();
	};						    
}