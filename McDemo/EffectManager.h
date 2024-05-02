#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/EventHandler.h"

namespace McCol
{
	class Transform;
	class Animation;
}

class Effect;
struct EffectInfo;
struct ID2D1Bitmap;

class EffectManager : public McCol::EventHandler
{
public:
	EffectManager();
	~EffectManager() override = default;

private:
	std::vector<std::pair<Effect*, int>> m_Effects;

public:
	void Initialize();
	void Finalize();
	void FixedUpdate(const float& deltaTime);
	void Render(McCol::D2DRender* renderer);

private:
	void LoadEffectBitmap();
	void CreateEffectObject(const EffectInfo& info);
	void RegisterEffect(std::any info);
};
