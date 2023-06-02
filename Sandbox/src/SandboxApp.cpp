#include <UnrealRuby.h>

#include "imgui/imgui.h"

class ExampleLayer : public UnrealRuby::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//UR_INFO("Update");

		if (UnrealRuby::Input::IsKeyPressed(UR_KEY_TAB))
			UR_TRACE("Tab Key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Science");
		ImGui::Text("The Earth Says Hello");
		ImGui::ColorEdit4("",new float[4]);
		ImGui::End();
	}

	void OnEvent(UnrealRuby::Event& event) override
	{
		//UR_TRACE("{0}",event);
	}
};

class Sandbox : public UnrealRuby::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

UnrealRuby::Application* UnrealRuby::CreateApplication()
{
	return new Sandbox;
}

