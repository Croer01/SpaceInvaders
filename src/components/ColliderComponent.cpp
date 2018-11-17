//
// Created by adria on 31/10/2018.
//

#include "ColliderComponent.hpp"
#include "../physics/PhysicsEngine.hpp"

namespace {
    Collider::ColliderShapes stringToColliderShape(const std::string &shapeName) {
        if(shapeName == "Box" || shapeName == "box")
            return Collider::ColliderShapes::Box;

        throw std::runtime_error("Unknown " + shapeName + " collider type.");
    }

    Collider::ColliderTypes stringToColliderType(const std::string &typeName) {
        if(typeName == "Static" || typeName == "static")
            return Collider::ColliderTypes::Static;
        else if(typeName == "Dynamic" || typeName == "dynamic")
            return Collider::ColliderTypes::Dynamic;
        else if(typeName == "Kinematic" || typeName == "kinematic")
            return Collider::ColliderTypes::Kinameatic;

        throw std::runtime_error("Unknown " + typeName + " collider type.");
    }
}
std::shared_ptr<Component> ColliderComponent::Clone() {
    std::shared_ptr<ColliderComponent> clone = std::make_shared<ColliderComponent>();
    clone->extends_ = extends_;
    clone->collider_ = collider_->clone();
    clone->collider_->setComponent(std::shared_ptr<ColliderComponent>(clone));
    PhysicsEngine::GetInstance().registerCollider(clone->collider_);
    return clone;
}

void ColliderComponent::fromFile(const YAML::Node &componentConfig) {
    std::shared_ptr<Collider> collider = std::make_shared<Collider>();
    collider->setShape(stringToColliderShape(componentConfig["colliderShape"].as<std::string>("Box")));
    collider->setType(stringToColliderType(componentConfig["colliderType"].as<std::string>("Static")));
    collider->setCategory(componentConfig["category"].as<std::string>(""));
    collider_ = collider;

    if(componentConfig["extends"]) {
        YAML::Node extendsNode = componentConfig["extends"];
        if(extendsNode.size() != 2 || extendsNode[0].as<float>() == 0 || extendsNode[1].as<float>() == 0){
            throw std::runtime_error("collider's extends configuration must be a sequence of 2 numbers greater than 0.");
        }
        extends_ = glm::vec2(extendsNode[0].as<float>(), extendsNode[1].as<float>());
    }
}

void ColliderComponent::init() {
    sprite_ = parent_->getComponent<SpriteComponent>();

    collider_->setPosition(convertWorldToPhysicsPos(parent_->getPosition()));
    collider_->setActive(parent_->isActive());
    if(extends_.x == 0 && extends_.y == 0)
        collider_->setSize(parent_->getScale().x/2.f, parent_->getScale().y/2.f);
    else
        collider_->setSize(extends_.x/2.f, extends_.y/2.f);

    collider_->registerObserver(this);
    parent_->registerObserver(this);
}

void ColliderComponent::Update(float elapsedTime) {
    if(collider_->getType() == Collider::ColliderTypes::Dynamic)
        parent_->setPosition(convertPhysicsToWorldPos(collider_->getPosition()));
}

void ColliderComponent::setOnColliderEnter(const OnColliderEventCallback &callback) {
    onColliderEnterCallback_ = callback;
}

void ColliderComponent::onEvent(const Subject<ColliderEvent> &target, const ColliderEvent &event, void *args) {
    if(event == ColliderEvent::BeginCollider && onColliderEnterCallback_) {
        Collider *collider = static_cast<Collider *>(args);
        if(auto component = collider->getComponent().lock())
            onColliderEnterCallback_(component.get());
    }
}

void ColliderComponent::onEvent(const Subject<GameObjectEvent> &target, const GameObjectEvent &event, void *args) {
    if(event == GameObjectEvent::PositionChanged){
        if(!parent_->isActive() || collider_->getType() != Collider::ColliderTypes::Dynamic)
            collider_->setPosition(convertWorldToPhysicsPos(parent_->getPosition()));
    }
    else if(event == GameObjectEvent::ScaleChanged){
        collider_->setSize(parent_->getScale().x/2.f, parent_->getScale().y/2.f);
    }
    else if(event == GameObjectEvent::ActiveChanged){
        collider_->setActive(parent_->isActive());
    }
}

ColliderComponent::~ColliderComponent() {
    if(collider_)
        PhysicsEngine::GetInstance().unregisterCollider(collider_);
}

void ColliderComponent::setVelocity(glm::vec3 velocity) {
    collider_->getBody()->SetLinearVelocity(b2Vec2(velocity.x,velocity.y));
}

void ColliderComponent::applyForce(glm::vec3 force) {
    collider_->getBody()->ApplyForceToCenter(b2Vec2(force.x,force.y), true);
}

glm::vec3 ColliderComponent::convertWorldToPhysicsPos(glm::vec3 worldPos) {
    if(auto sprite = sprite_.lock()) {
        float xOffset = sprite->getWidth() / 2.f;
        float yOffset = sprite->getHeight() / 2.f;
        return worldPos + glm::vec3(xOffset, yOffset, 0.f);
    }
    return glm::vec3(0);
}

glm::vec3 ColliderComponent::convertPhysicsToWorldPos(glm::vec3 physicsPos) {
    if(auto sprite = sprite_.lock()) {
        float xOffset = sprite->getWidth()/2.f;
        float yOffset = sprite->getHeight()/2.f;
        return physicsPos - glm::vec3(xOffset,yOffset,0.f);
    }
    return glm::vec3(0);
}

