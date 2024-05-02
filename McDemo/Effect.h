#pragma once
#include "../Engine/GameObject.h"

namespace McCol
{
	class Transform;
	class Animation;
	class TextureRenderer;
}

enum class EffectType;

class Effect : public McCol::GameObject
{
public:
	Effect();
	~Effect() override = default;

private:
	float m_PlayTime;
	float m_ProgressTime;
	McCol::Transform* m_Transform;
	McCol::Animation* m_Animation;
	McCol::TextureRenderer* m_TextureRenderer;

public:
	void Initialize() override;
	void FixedUpdate(const float& deltaTime) override;
	void Render(McCol::D2DRender* renderer) override;

	void LoadEffect(EffectType type);
	void SetPosition(float x, float y);
	void SetValue(int value);
	void OnFadeOut();
};
