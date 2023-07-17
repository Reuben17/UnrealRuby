#include <UnrealRuby.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
# include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public UnrealRuby::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(UnrealRuby::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f,-0.5f,0.0f, 0.8f,0.2f,0.8f,1.0f,
			 0.5f,-0.5f,0.0f, 0.2f,0.3f,1.0f,1.0f,
			 0.0f, 0.5f,0.0f, 0.8f,0.8f,0.2f,1.0f
		};

		UnrealRuby::Ref<UnrealRuby::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(UnrealRuby::VertexBuffer::Create(vertices, sizeof(vertices)));

		UnrealRuby::BufferLayout layout{
			{UnrealRuby::ShaderDataType::Float3,"a_Position"},
			{UnrealRuby::ShaderDataType::Float4,"a_Color"}
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		UnrealRuby::Ref<UnrealRuby::IndexBuffer> indexBuffer;
		indexBuffer.reset(UnrealRuby::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(UnrealRuby::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		UnrealRuby::Ref<UnrealRuby::VertexBuffer> squareVB;
		squareVB.reset(UnrealRuby::VertexBuffer::Create(squareVertices, sizeof(squareVertices))); 

		squareVB->SetLayout({
			{UnrealRuby::ShaderDataType::Float3,"a_Position" },
			{UnrealRuby::ShaderDataType::Float2,"a_TexCoord" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		UnrealRuby::Ref<UnrealRuby::IndexBuffer> squareIB;
		squareIB.reset(UnrealRuby::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{	
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5,1.0);
				color = v_Color;
			}
		)";

		m_Shader = UnrealRuby::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);


		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{	
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color,1.0);
			}
		)";

		m_FlatColorShader =UnrealRuby::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = UnrealRuby::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = UnrealRuby::Texture2D::Create("assets/textures/Midas.png");

		std::dynamic_pointer_cast<UnrealRuby::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<UnrealRuby::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(UnrealRuby::Timestep ts) override
	{
		if (UnrealRuby::Input::IsKeyPressed(UR_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		else if (UnrealRuby::Input::IsKeyPressed(UR_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;


		if (UnrealRuby::Input::IsKeyPressed(UR_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		else if (UnrealRuby::Input::IsKeyPressed(UR_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		 
		if (UnrealRuby::Input::IsKeyPressed(UR_KEY_A)) 
			m_CameraRotation += m_CameraRotationSpeed * ts;

		if (UnrealRuby::Input::IsKeyPressed(UR_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		UnrealRuby::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		UnrealRuby::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);	
		m_Camera.SetRotation(m_CameraRotation);

		UnrealRuby::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<UnrealRuby::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<UnrealRuby::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color",m_SquareColor);

		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 16; x++)
			{
				glm::vec3 pos(x * 0.11f,y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				UnrealRuby::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
	
		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		UnrealRuby::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		UnrealRuby::Renderer::Submit(textureShader, m_SquareVA,glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//UnrealRuby::Renderer::Submit(m_Shader, m_VertexArray); 

		UnrealRuby::Renderer::EndScene(); 
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color",glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(UnrealRuby::Event& event) override
	{

	}

private:
	UnrealRuby::ShaderLibrary m_ShaderLibrary;
	UnrealRuby::Ref<UnrealRuby::Shader> m_Shader; 
	UnrealRuby::Ref<UnrealRuby::Shader> m_FlatColorShader;

	UnrealRuby::Ref<UnrealRuby::VertexArray> m_VertexArray;
	UnrealRuby::Ref<UnrealRuby::VertexArray> m_SquareVA;

	UnrealRuby::Ref<UnrealRuby::Texture2D> m_Texture, m_ChernoLogoTexture;

	UnrealRuby::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.8f,0.5f,0.8f };

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



