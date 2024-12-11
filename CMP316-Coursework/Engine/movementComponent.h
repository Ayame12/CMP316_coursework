#pragma once
#include "ENUM_TYPES.h"
#include "Component.h"

class MovementComponent : public Component {
public:
    MovementComponent(int mt, int up, int down, int left, int right, float s) {
        moveType = static_cast<MOVEMENT_TYPES>(mt);
        controlls[0] = up;
        controlls[1] = down;
        controlls[2] = left;
        controlls[3] = right;
        speed = s;
    };

    void handleInput(GameObject* gameObject, float dt) override;

    void update(GameObject* gameObject, float dt) override;

    void setControlls(int up, int down, int left, int right) {};

private:
    MOVEMENT_TYPES moveType;
    sf::Vector2f velocity;
    float speed = 200.0f;
    int controlls[4];
};
