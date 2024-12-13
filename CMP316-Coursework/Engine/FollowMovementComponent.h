#pragma once
#include "Component.h"

class GameObject;

class FollowMovementComponent : public Component {
public:

    FollowMovementComponent(GameObject* t, float s, float dk) { target = t; speed = s; distKept = dk; };

    void handleInput(GameObject* gameObject, float dt) override;

    void update(GameObject* gameObject, float dt) override;

private:
    GameObject* target;
    float speed;
    float distKept;
};

