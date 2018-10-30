//
// Created by adria on 29/10/2018.
//

#ifndef SPACEINVADERS_PLAYERCOMPONENT_HPP
#define SPACEINVADERS_PLAYERCOMPONENT_HPP


#include "src/Component.hpp"
#include "BulletComponent.hpp"

COMPONENT(PlayerComponent)
class PlayerComponent : public Component {
    std::shared_ptr<GameObject> bullet_;
    float speed_;
public:
    void init() override;

    void Update(float elapsedTime) override;

    std::shared_ptr<Component> Clone() override;

    void fromFile(const YAML::Node &componentConfig) override;
};


#endif //SPACEINVADERS_PLAYERCOMPONENT_HPP
