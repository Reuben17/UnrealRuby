#include <UnrealRuby.h>

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
		PushOverlay(new UnrealRuby::ImGuiLayer);
	}
	~Sandbox()
	{

	}
};

UnrealRuby::Application* UnrealRuby::CreateApplication()
{
	return new Sandbox;
}

