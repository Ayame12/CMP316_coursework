#pragma once
#include "Component.h"
class PatrolMovementComponent : public Component
{
public:
    PatrolMovementComponent(const std::vector<sf::Vector2f> p, float s) { patrolPoints = p; speed = s; };

    void handleInput(GameObject* gameObject, float dt) override;

    void update(GameObject* gameObject, float dt) override;

private:
    std::vector<sf::Vector2f> patrolPoints;
    float speed;
    size_t currentTargetIndex = 0;
};

