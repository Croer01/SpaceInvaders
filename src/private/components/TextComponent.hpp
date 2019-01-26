//
// Created by adria on 04/11/2018.
//

#ifndef SPACEINVADERS_TEXTCOMPONENT_HPP
#define SPACEINVADERS_TEXTCOMPONENT_HPP


#include "../Component.hpp"
#include "../graphics/font/Text.hpp"
namespace GameEngine {
namespace Internal {
    class TextComponent : public Component, public Observer<GameObjectEvent> {
        std::string text_;
        std::string font_;
        unsigned int fontSize_;
        std::shared_ptr<Text> textGraphic_;
        bool visible_;

        void updateTextTransform();

    public:
        virtual ~TextComponent();

        void init() override;

        std::shared_ptr<Component> Clone() override;

        void fromFile(const YAML::Node &componentConfig) override;

        void onEvent(const Subject<GameObjectEvent> &target, const GameObjectEvent &event, void *args) override;

        //Text public API
        void setText(const std::string &text);

        void setVisible(bool visible);

        bool isVisible() const;

    protected:
        void onGameObjectChange(GameObject *oldGameObject, GameObject *newGameObject) override;
    };
}
}

#endif //SPACEINVADERS_TEXTCOMPONENT_HPP