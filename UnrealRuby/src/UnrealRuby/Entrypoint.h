#pragma once

#ifdef  UR_PLATFORM_WINDOWS

extern UnrealRuby::Application* UnrealRuby::CreateApplication();

int main(int argc,char** argv)
{
	UnrealRuby::Log::Init();
	UR_CORE_WARN("Initialzied!");
	UR_ERROR("Initialzied!");

	auto app = UnrealRuby::CreateApplication();
	app->Run();
	delete app;

}
#endif