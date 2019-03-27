//
// Created by adria on 27/03/2019.
//

#include <game-engine/components/TextComponent.hpp>
#include <game-engine/geIO.hpp>
#include "HighScoreLoaderComponent.hpp"

void HighScoreLoaderComponent::init() {
    const std::weak_ptr<GameEngine::TextComponent> &textRef = gameObject()->getComponent<GameEngine::TextComponent>();

    if(auto text = textRef.lock()){
        int score = 0;

        GameEngine::geIO io;

        const GameEngine::geDataRef &loadedData = io.load("score.save");
        if(loadedData->hasValue("score")) {
            score = loadedData->getInt("score");
        }

        text->text(text->text() + "hi-score = " + std::to_string(score));
    }
}
