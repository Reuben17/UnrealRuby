#include "urpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace UnrealRuby
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: UR_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		UR_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}