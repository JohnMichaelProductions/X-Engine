#pragma once
#include "XEngine.h"
#include "ParticleSystem.h"
class MainLayer : public XEngine::Layer
{
public:
	MainLayer();
	virtual ~MainLayer() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(XEngine::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(XEngine::Event& e) override;
private:
	// Temp
	XEngine::OrthographicCameraController mainCamera;
	XEngine::Ref<XEngine::VertexArray> mainVertexArray;
	XEngine::Ref<XEngine::Shader> mainShader;
	// Textures
	XEngine::Ref<XEngine::Texture2D> checkerboardTexture;
	XEngine::Ref<XEngine::Texture2D> spriteSheet;
	XEngine::Ref<XEngine::SubTexture2D> treeTexture;
	glm::vec4 mainColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	ParticleSystem mainParticleSystem;
	ParticleProps mainParticle;
};