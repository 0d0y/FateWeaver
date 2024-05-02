#pragma once
#include "../Engine/TextRenderer.h"

class CardText : public McCol::TextRenderer
{
public:
    CardText(McCol::GameObject* owner);
    ~CardText() override;

public:
    void Render(McCol::D2DRender* renderer) override;


};

