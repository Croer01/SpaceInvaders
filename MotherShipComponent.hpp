//
// Created by adria on 23/11/2018.
//

#ifndef SPACEINVADERS_MOTHERSHIPCOMPONENT_HPP
#define SPACEINVADERS_MOTHERSHIPCOMPONENT_HPP

#include "src/Component.hpp"
#include "EnemyManagerComponent.hpp"

COMPONENT(MotherShipComponent);
class MotherShipComponent : public Component, public Observer<GameObjectEvent> {
    int minPoints_;
    int maxPoints_;
    int points_;
    int pointsPerBullet_;

    float speed_;
    std::weak_ptr<GameObject> playerBullet_;
    std::weak_ptr<EnemyManagerComponent> enemyManager_;
    std::weak_ptr<GameObject> scoreText_;

public:
    void init() override;

    void Update(float elapsedTime) override;

    std::shared_ptr<Component> Clone() override;

    void fromFile(const YAML::Node &componentConfig) override;

    void kill();

    void onEvent(const Subject<GameObjectEvent> &target, const GameObjectEvent &event, void *args) override;

    //public Mothership functions
    void hide();

};


#endif //SPACEINVADERS_MOTHERSHIPCOMPONENT_HPP