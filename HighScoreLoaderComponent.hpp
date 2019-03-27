//
// Created by adria on 27/03/2019.
//

#ifndef SPACEINVADERS_SCORELOADERCOMPONENT_HPP
#define SPACEINVADERS_SCORELOADERCOMPONENT_HPP


#include <game-engine/geComponent.hpp>

COMPONENT(HighScoreLoaderComponent)
class HighScoreLoaderComponent : public GameEngine::geComponentInstantiable<HighScoreLoaderComponent> {
public:
    void init() override;
};


#endif //SPACEINVADERS_SCORELOADERCOMPONENT_HPP
