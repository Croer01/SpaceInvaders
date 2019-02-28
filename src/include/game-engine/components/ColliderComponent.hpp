//
// Created by adria on 31/10/2018.
//

#ifndef SPACEINVADERS_COLLIDERCOMPONENT_HPP
#define SPACEINVADERS_COLLIDERCOMPONENT_HPP

#include <game-engine/geComponent.hpp>
#include <game-engine/components/SpriteComponent.hpp>
#include "../private/physics/Collider.hpp"
#include "SpriteAnimatedComponent.hpp"

namespace GameEngine {
    class ColliderComponent;

    typedef std::function<void(ColliderComponent *)> OnColliderEventCallback;

    class ColliderComponent : public geComponent, public Observer<Internal::ColliderEvent>, public Observer<GameObjectEvent> {
        std::shared_ptr<Internal::Collider> collider_;
        OnColliderEventCallback onColliderEnterCallback_;
        std::weak_ptr<SpriteComponent> sprite_;
        std::weak_ptr<SpriteAnimatedComponent> spriteAnimated_;
        Vec2D extends_;
        Vec2D offset_;
        std::string colliderShape_;
        std::string colliderType_;
        std::string colliderCategory_;

        Vec2D convertWorldToPhysicsPos(const Vec2D &worldPos) const;

        Vec2D convertPhysicsToWorldPos(const Vec2D &physicsPos) const;

    public:
        virtual ~ColliderComponent();

        void init() override;

        void Update(float elapsedTime) override;

        //Component collider public API
        void setOnColliderEnter(const OnColliderEventCallback &callback);

        void setVelocity(glm::vec3 velocity);

        void applyForce(glm::vec3 force);

        Vec2D extends() const;
        void extends(const Vec2D &extends);
        Vec2D offset() const;
        void offset(const Vec2D &offsetValue);
        std::string shape() const;
        void shape(const std::string &colliderShape);
        std::string type() const;
        void type(const std::string &colliderType);
        std::string category() const;
        void category(const std::string &colliderCategory);

    protected:
        PropertySetBase *configureProperties() override;

    protected:
        void onEvent(const Subject<Internal::ColliderEvent> &target, const Internal::ColliderEvent &event, void *args) override;

        void onEvent(const Subject<GameObjectEvent> &target, const GameObjectEvent &event, void *args) override;

        void onGameObjectChange(GameEngine::geGameObject *oldGameObject, GameEngine::geGameObject *newGameObject) override;
    };
}

#endif //SPACEINVADERS_COLLIDERCOMPONENT_HPP