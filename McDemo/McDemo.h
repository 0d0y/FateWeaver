#pragma once
#include "../Engine/Mengine.h"

class EffectManager;

class McDemo final : public McCol::Mengine
{
public:
	McDemo();
	~McDemo() override;

private:
	EffectManager* m_EffectManager;

public:
	/*Init*/
	HRESULT Initialize(HINSTANCE hInst, const char* appName) override;
	/*unInit*/
	void Finalize() override;

protected:
	void UpdateAll(const float& deltaTime) override;
	void RenderAll() override;
};