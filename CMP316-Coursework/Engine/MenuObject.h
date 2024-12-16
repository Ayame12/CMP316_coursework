#pragma once
class MenuObject : public sf::RectangleShape
{
public:
	virtual void handleInput(float dt);
	virtual void update(float dt);

	bool isButton = false;
	sf::Text text;
	sf::Texture* NormalTex;
	sf::Texture* HighTex;
	int target = 1;
};

