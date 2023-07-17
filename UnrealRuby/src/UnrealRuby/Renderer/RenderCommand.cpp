#include "urpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace UnrealRuby {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

