#include "pch.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "ENUM_TYPES.h"

Animation::Animation()
{

}

//based on the parameters store the frames in a vector to be accessed in a sequence later
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
	//check animation is not stopped
	if (isPlaying)
	{
		//check enough time passed between frames
		timePassed += dt;
		if (timePassed >= speed)
		{
			//check the frames vector doesnt go out of scope
			currentFrame++;
			if (currentFrame >= frames.size())
			{
				//if it does go out of scope
				//if it loops reset to 0
				if (loop)
				{
					currentFrame = 0;
				}
				//if it doesnt set playing to false
				else
				{
					currentFrame--;
					isPlaying = false;
				}
			}
			//reset timer
			timePassed = 0;
		}
	}
}

sf::IntRect Animation::getCurrentFrame()
{
	//return the current drame from the vector 
	frame = frames[currentFrame];
	//if the object is flipped flip the frame to math animation to movement
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
	//set appropriate animation based on the state of the object
	int prevAnimation = currentAnimation;

	//if it is not moving
	if (gameobj->getVelocity().x == 0 && gameobj->getVelocity().y == 0)
	{
		currentAnimation = 0;
	}
	//if it is moving mainly horisontaly
	else if (gameobj->getVelocity().x * gameobj->getVelocity().x > gameobj->getVelocity().y * gameobj->getVelocity().y)
	{
		currentAnimation = 3;
	}
	//if it is moving mainly verticaly
	else if (gameobj->getVelocity().x * gameobj->getVelocity().x < gameobj->getVelocity().y * gameobj->getVelocity().y)
	{
		//different animations for walking up or doen (front of the character and back)
		if (gameobj->getVelocity().y < 0)
		{
			currentAnimation = 1;
		}
		else
		{
			currentAnimation = 2;
		}
	}
	//separate animation if the character is hurt
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
	//change previous animation to is not playing
	animation->setPlaying(false);	
	//change animation ponter to current one
	animation = &animations[currentAnimation];
	//if the animation has been changed, reset the frames so that animation doesnt start in the middle
	if (prevAnimation != currentAnimation)
	{
		animation->setCurrentFrame(0);
	}
	//play current animayion
	animation->setPlaying(true);
	animation->setFlipped(gameobj->getFlipped());
	animation->animate(dt);
	//set texture of the obj to the current frame
	gameobj->setTextureRect(animation->getCurrentFrame());
}