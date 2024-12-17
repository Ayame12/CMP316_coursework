#pragma once
#include "Component.h"

//component that takes in user input to move the object

class PlayerMovementComponent : public Component {
public:
    PlayerMovementComponent(int up, int down, int left, int right, float s) {
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
    float speed = 200.0f;
    int controlls[4];
};
