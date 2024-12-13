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

AnimationComponent::AnimationComponent(int ani[9][5], float s[9], bool l[9])
{
	for (int i = 0; i < 9; ++i)
	{
		animations[i].setUp(ani[i][0], ani[i][1], ani[i][2], ani[i][3], ani[i][4], s[i], l[i]);
	}
}

void AnimationComponent::handleInput(GameObject* gameObj, float dt)
{
}

void AnimationComponent::update(GameObject* gameobj, float dt)
{
	prevAnimation = currentAnimation;
	if (gameobj->getVelocity().x == 0 && gameobj->getVelocity().y == 0)
	{
		currentAnimation = 0;
	}
	else if (gameobj->getVelocity().x != 0 && gameobj->getVelocity().y == 0)
	{
		currentAnimation = 2;
	}
	else if (gameobj->getVelocity().x == 0 && gameobj->getVelocity().y != 0)
	{
		currentAnimation = 1;
	}

	if (prevAnimation != currentAnimation)
	{
		animation->setPlaying(false);
	}

	animation = &animations[currentAnimation];
	animation->animate(dt);
	gameobj->setTextureRect(animation->getCurrentFrame());
}