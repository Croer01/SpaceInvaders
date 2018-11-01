//
// Created by adria on 31/10/2018.
//

#ifndef SPACEINVADERS_COLLIDERCOMPONENT_HPP
#define SPACEINVADERS_COLLIDERCOMPONENT_HPP


#include "../Component.hpp"
#include "../physics/Collider.hpp"
#include "SpriteComponent.hpp"

class ColliderComponent;
typedef std::function<void (const std::shared_ptr<ColliderComponent> &)> OnColliderEventCallback;

class ColliderComponent : public Component, public Observer<ColliderEvent>, public Observer<GameObjectEvent>{
    std::shared_ptr<Collider> collider_;
    OnColliderEventCallback onColliderEnterCallback_;
    std::shared_ptr<SpriteComponent> sprite_;
    glm::vec2 extends_;

    glm::vec3 convertWorldToPhysicsPos(glm::vec3 worldPos);
    glm::vec3 convertPhysicsToWorldPos(glm::vec3 physicsPos);
public:
    virtual ~ColliderComponent();

    std::shared_ptr<Component> Clone() override;

    void init() override;

    void Update(float elapsedTime) override;

    void fromFile(const YAML::Node &componentConfig) override;

    void onEvent(const Subject<ColliderEvent> &target, const ColliderEvent &event, void *args) override;
    void onEvent(const Subject<GameObjectEvent> &target, const GameObjectEvent &event, void *args) override;

    //Component collider public API
    void setOnColliderEnter(const OnColliderEventCallback &callback);
    void setVelocity(glm::vec3 velocity);
    void applyForce(glm::vec3 force);

};


#endif //SPACEINVADERS_COLLIDERCOMPONENT_HPP