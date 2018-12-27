//
// Created by adria on 27/12/2018.
//

#include "AudioComponent.hpp"
#include "../audio/AudioEngine.hpp"

void AudioComponent::init() {
    if(playOnInit_)
        play();
}

std::shared_ptr<Component> AudioComponent::Clone() {
    std::shared_ptr<AudioComponent> clone = std::make_shared<AudioComponent>();
    clone->filePath_ = filePath_;
    clone->playOnInit_ = playOnInit_;
    clone->source_ = AudioEngine::GetInstance().getAudio(filePath_);

    return clone;
}

void AudioComponent::fromFile(const YAML::Node &componentConfig) {
    if(!componentConfig["filePath"])
        throw std::logic_error("property filePath not defined");
    filePath_ = componentConfig["filePath"].as<std::string>();
    playOnInit_ = componentConfig["playOnInit"].as<bool>(false);
}

void AudioComponent::play() {
    stop();
    source_->play();
}

bool AudioComponent::isPlaying() {
    return source_->isPlaying();
}

void AudioComponent::stop() {
    if(isPlaying())
        source_->stop();
}
