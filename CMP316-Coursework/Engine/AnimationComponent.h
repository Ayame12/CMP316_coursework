#pragma once
#include "Component.h"

class GameObject;

class Animation
{
public:
    Animation();
    
    void setUp(int x, int y, int width, int height, int fNo, float s, bool l);
    void animate( float dt);
    void setFlipped(bool f) { isFlipped = f; };
    void setPlaying(bool p) { isPlaying = p; };

    sf::IntRect getCurrentFrame();
    void setCurrentFrame(int f) { currentFrame = f; };

private:

    float timePassed = 0;
    float speed = 0;
    bool isPlaying = true;
    bool loop = true;
    bool isFlipped = false;

    int currentFrame = 0;

    sf::IntRect frame;
    std::vector<sf::IntRect>frames;
};

class AnimationComponent : public Component
{
public:
    AnimationComponent(int ani[9][5], float s[9], bool isLooping[9]);

    void handleInput(GameObject* gameObject, float dt) override;
    void update(GameObject* gameObject, float dt) override;

private:

    //int animations[9][5];
    Animation animations[9];
    Animation* animation = &animations[0];
    int currentAnimation = 1;
    int prevAnimation = 0;
};