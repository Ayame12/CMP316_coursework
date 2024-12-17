#pragma once

class GameObject;

//base component that allows me to make other components inhereting from it and adding them all to a single
//vector inside the object so that every object is responsable with updating its own components

class Component {
public:
    virtual ~Component() = default;

    virtual void handleInput(GameObject* gameObject, float dt) = 0;
    virtual void update(GameObject* gameObject, float dt) = 0;
};
