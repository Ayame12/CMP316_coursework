#pragma once

class GameObject; // Forward declaration

class Component {
public:
    virtual ~Component() = default;

    virtual void handleInput(GameObject* gameObject, float dt) = 0;
    virtual void update(GameObject* gameObject, float dt) = 0;
};
