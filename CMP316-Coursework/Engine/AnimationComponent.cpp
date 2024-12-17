#include "pch.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "ENUM_TYPES.h"

Animation::Animation()
{

}

void Animation::setUp(int x, int y, int width, int height, int fNo, float s, bool isLooping)
{
	speed = s;
	for (int i = 0; i < fNo; i++)
	{
		frames.push_back(sf::IntRect(x + width * i, y , width, height));
	}
	loop = isLooping;
}

void Animation::animate(float dt)
{
	if (isPlaying)
	{
		timePassed += dt;
		if (timePassed >= speed)
		{
			currentFrame++;
			if (currentFrame >= frames.size())
			{
				if (loop)
				{
					currentFrame = 0;
				}
				else
				{
					currentFrame--;
					isPlaying = false;
				}
			}
			timePassed = 0;
		}
	}
}

sf::IntRect Animation::getCurrentFrame()
{
	frame = frames[currentFrame];
	if (isFlipped)
	{

		frame = sf::IntRect(frame.left + frame.width, frame.top, -frame.width, frame.height);
	}
	return frame;
}

AnimationComponent::AnimationComponent(int ani[5][5], float s[5], bool l[5])
{
	for (int i = 0; i < 5; ++i)
	{
		animations[i].setUp(ani[i][0], ani[i][1], ani[i][2], ani[i][3], ani[i][4], s[i], l[i]);
	}
}

void AnimationComponent::handleInput(GameObject* gameObj, float dt)
{
}

void AnimationComponent::update(GameObject* gameobj, float dt)
{
	int prevAnimation = currentAnimation;
	if (gameobj->getVelocity().x == 0 && gameobj->getVelocity().y == 0)
	{
		currentAnimation = 0;
	}
	else if (gameobj->getVelocity().x * gameobj->getVelocity().x > gameobj->getVelocity().y * gameobj->getVelocity().y)
	{
		currentAnimation = 3;
	}
	else if (gameobj->getVelocity().x * gameobj->getVelocity().x < gameobj->getVelocity().y * gameobj->getVelocity().y)
	{
		if (gameobj->getVelocity().y < 0)
		{
			currentAnimation = 1;
		}
		else
		{
			currentAnimation = 2;
		}
	}
	if (gameobj->hurt)
	{
		hurtTimer += dt;
		if (hurtTimer >= maxHurtTimer)
		{
			hurtTimer = 0;
			gameobj->hurt = false;
		}
		currentAnimation = 4;
	}
	animation->setPlaying(false);	
	animation = &animations[currentAnimation];
	if (prevAnimation != currentAnimation)
	{
		animation->setCurrentFrame(0);
	}
	animation->setPlaying(true);
	animation->setFlipped(gameobj->getFlipped());
	animation->animate(dt);
	gameobj->setTextureRect(animation->getCurrentFrame());
}